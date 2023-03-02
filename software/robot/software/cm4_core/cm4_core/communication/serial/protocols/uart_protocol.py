import typing

import cm4_core.communication.protocol as protocol


# noinspection PyTypeChecker
class UART_Message(protocol.Message):
    cmd: int
    flag: int
    add: list
    data: typing.Union[list, bytes]


class UART_Protocol(protocol.Protocol):
    """
       |   BYTE    |   NAME            |   DESCRIPTION                 |   VALUE
       |   0       |   HEADER[0]       |   Header byte                 |   0x55
       |   3       |   CMD             |   Command                     |
       |   1       |   ADD[0]          |   Address                     |
       |   2       |   ADD[1]          |   Address                     |
       |   2       |   ADD[2]          |   Address                     |
       |   3       |   FLAG            |   Flag                        |
       |   5       |   LEN             |   Length of the payload       |
       |   6       |   PAYLOAD[0]      |   Payload                     |
       |   6+N-1   |   PAYLOAD[N-1]    |   Payload                     |
       |   6+N     |   CRC8            |   CRC8 of the Payload         |
       """
    base_protocol = None
    protocol_identifier = 0
    Message = UART_Message

    idx_header = 0
    header = 0x55
    idx_cmd = 1
    idx_add_0 = 2
    idx_add_1 = 3
    idx_add_2 = 4
    idx_flag = 5
    idx_len = 6
    idx_payload = 7
    offset_crc8 = 7

    protocol_overhead = 8

    @classmethod
    def decode(cls, data):
        """

        :param data:
        :return:
        """
        msg = cls.Message()

        payload_len = data[cls.idx_len]

        msg.cmd = data[cls.idx_cmd]
        msg.flag = data[cls.idx_flag]
        msg.add = data[cls.idx_add_0:cls.idx_add_2+1]
        msg.data = data[cls.idx_payload:cls.idx_payload + payload_len]

        return msg

    @classmethod
    def encode(cls, msg: UART_Message):
        """

        :param msg:
        :return:
        """
        buffer = [0] * (cls.protocol_overhead + len(msg.data))

        buffer[cls.idx_header] = cls.header
        buffer[cls.idx_cmd] = msg.cmd
        buffer[cls.idx_add_0:cls.idx_add_2+1] = msg.add
        buffer[cls.idx_flag] = msg.flag
        buffer[cls.idx_len] = len(msg.data)
        buffer[cls.idx_payload:cls.idx_payload + len(msg.data)] = msg.data
        buffer[cls.offset_crc8 + len(msg.data)] = 0
        buffer = bytes(buffer)
        return buffer

    @classmethod
    def check(cls, data):
        """

        :param data:
        :return:
        """
        payload_len = data[cls.idx_len]

        if not data[cls.idx_header] == cls.header:
            return 0

        if not len(data) == (payload_len + cls.protocol_overhead):
            return 0


UART_Message._protocol = UART_Protocol
