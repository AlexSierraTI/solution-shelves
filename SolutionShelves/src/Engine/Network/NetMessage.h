#pragma once

#include "Engine/Core/Assert.h"

namespace SolutionShelves
{
	template <typename T>
	struct message_header
	{
		T id{};
		size_t size = 0;
	};

	template <typename T>
	struct message
	{
		message_header<T> header{};
		std::vector<uint8_t> body;

		size_t size() const
		{
			return sizeof(message_header<T>) + body.size();
		}

		friend std::ostream& operator << (std::ostream& os, const message<T>& msg)
		{
			os << "ID:" << int(msg.header.id) << " Tamanho:" << msg.header.size;
			return os;
		}

		template <typename DataType>
		friend message<T>& operator << (message<T>& msg, const DataType& data)
		{
			SS_ASSERT(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");
			size_t i = msg.body.size();

			msg.body.resize(msg.body.size() + sizeof(DataType));

			std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

			msg.header.size = msg.body.size();

			return msg;
		}

		template <typename DataType>
		friend message<T>& operator >> (message<T>& msg, DataType& data)
		{
			SS_ASSERT(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

			size_t i = msg.body.size() - sizeof(DataType);

			std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

			msg.body.resize(i);

			msg.header.size = msg.body.size();

			return msg;
		}
	};

	template <typename T>
	class connection;

	template <typename T>
	struct owned_message
	{
		Ref<connection<T>> remote = nullptr;
		message<T> msg;

		friend std::ostream& operator << (std::ostream& os, const owned_message<T>& msg)
		{
			os << msg.msg;
			return os;
		}
	};
}
