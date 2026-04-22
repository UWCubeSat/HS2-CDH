module TmtcRadioTypes {
    struct TmtcRadioPacket {
        preamble: [10] U8,
        sync_word: U32,
        payload_length: [1] U8, # Length of payload plus length and address bytes
        address: [1] U8, # Address of radio  (Tx: 0x33, Rx: 0x32) 
        payload: [128] U8, # 0 - 240
        crc32: [4] U8 # CRC-32 algorithm, polynomial = Polynomial: 0x04C11DB7, seed = 0xFFFFFFFF (configurable)
    } default {preamble = 0xAA, sync_word = 0x33553355}
}
