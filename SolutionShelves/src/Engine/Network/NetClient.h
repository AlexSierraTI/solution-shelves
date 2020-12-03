#pragma once

#include "NetMessage.h"
#include "NetTsQueue.h"
#include "NetConnection.h"

namespace SolutionShelves
{
	template <typename T>
	class client_interface
	{
	public:
		client_interface()
		{
		}

		~client_interface()
		{
			Disconnect();
		}

		bool Connect(const std::string& host, const uint16_t port)
		{
			try
			{
				asio::ip::tcp::resolver resolver(m_context);
				asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

				m_connection = CreateScope<connection<T>>(
					connection<T>::owner::client,
					m_context,
					asio::ip::tcp::socket(m_context), m_qMessagesIn);

				m_connection->ConnectToServer(endpoints);

				thrContext = std::thread([this]() { m_context.run(); });
			}
			catch (std::exception& e)
			{
				SS_CORE_ERROR("Client Exception: {0}", e.what());
				return false;
			}
			return false;
		}

		void Disconnect()
		{
			if (IsConnected())
			{
				m_connection->Disconnect();
			}
			m_context.stop();
			if (thrContext.joinable())
				thrContext.join();

			m_connection.release();
		}

		bool IsConnected()
		{
			if (m_connection)
				return m_connection->IsConnected();
			else
				return false;
		}

		tsqueue<owned_message<T>>& Incoming()
		{
			return m_qMessagesIn;
		}

		void Send(const message<T>& msg)
		{
			m_connection->Send(msg);
		}

	protected:
		asio::io_context m_context;
		std::thread thrContext;
		Scope<connection<T>> m_connection;
	private:
		tsqueue<owned_message<T>> m_qMessagesIn;
	};
}
