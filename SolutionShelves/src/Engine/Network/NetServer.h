#pragma once

#include "NetMessage.h"
#include "NetTsQueue.h"
#include "NetConnection.h"

namespace SolutionShelves
{
	template <typename T>
	class server_interface
	{
	public:
		server_interface(uint16_t port)
			: m_asioAcceptor(m_asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
		{

		}

		virtual ~server_interface()
		{
			Stop();
		}

		bool Start()
		{
			try
			{
				WaitForClientConnection();

				m_threadContext = std::thread([this]() { m_asioContext.run(); });
			}
			catch (std::exception& e)
			{
				SS_CORE_ERROR("[SERVER] Exception: {0}", e.what());
				return false;
			}

			SS_CORE_INFO("[SERVER] Server Started!");
			return true;
		}

		void Stop()
		{
			m_asioContext.stop();

			if (m_threadContext.joinable()) m_threadContext.join();
		}

		void WaitForClientConnection() // ASYNC
		{
			m_asioAcceptor.async_accept(
				[this](std::error_code ec, asio::ip::tcp::socket socket)
				{
					if (!ec)
					{
						SS_CORE_INFO("[SERVER] New Connection: {0}", socket.remote_endpoint());

						std::shared_ptr<connection<T>> newconn =
							std::make_shared<connection<T>>(connection<T>::owner::server,
								m_asioContext, std::move(socket), m_qMessagesIn);

						if (OnClientConnect(newconn))
						{
							m_deqConnections.push_back(std::move(newconn));
							m_deqConnections.back()->ConnectToClient(this, m_IDCounter++);

							SS_CORE_INFO("[{0}] Connection Approved", m_deqConnections.back()->GetID());
						}
						else
						{
							SS_CORE_WARN("[-----] Connection Denied");
						}
					}
					else
					{
						SS_CORE_ERROR("[SERVER] ERRO: {0}", ec.message());
					}

					WaitForClientConnection();
				});
		}

		void MessageClient(Ref<connection<T>> client, const message<T>& msg)
		{
			if (client && client->IsConnected())
			{
				client->Send(msg);
			}
			else
			{
				OnClientDisconnect(client);
				client.reset();
				m_deqConnections.erase(
					std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end());
			}
		}

		void MessageAllClients(const message<T>& msg, Ref<connection<T>> pIgnoreClient = nullptr)
		{
			bool bInvalidClientExists = false;
			for (auto& client : m_deqConnections)
			{
				if (client && client->IsConnected())
				{
					if (client != pIgnoreClient)
						client->Send(msg);
				}
				else
				{
					OnClientDisconnect(client);
					client.reset();
					bInvalidClientExists = true;
				}
			}

			if (bInvalidClientExists)
			{
				m_deqConnections.erase(
					std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr), m_deqConnections.end());
			}

		}

		void Update(size_t nMaxMessages = -1, bool bWait = false)
		{
			if (bWait) m_qMessagesIn.wait();

			size_t nMessageCount = 0;
			while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty())
			{
				auto msg = m_qMessagesIn.pop_front();

				OnMessage(msg.remote, msg.msg);

				nMessageCount++;
			}
		}

	protected:
		virtual bool OnClientConnect(Ref<connection<T>> client)
		{
			return false;
		}

		virtual void OnClientDisconnect(Ref<connection<T>> client)
		{

		}

		virtual void OnMessage(Ref<connection<T>> client, message<T>& msg)
		{

		}

	public:
		virtual void OnClientValidated(Ref<connection<T>> client)
		{
		}

	protected:
		tsqueue<owned_message<T>> m_qMessagesIn;

		std::deque<Ref<connection<T>>> m_deqConnections;

		asio::io_context m_asioContext;
		std::thread m_threadContext;

		asio::ip::tcp::acceptor m_asioAcceptor;

		uint32_t m_IDCounter = 10000;
	};
}
