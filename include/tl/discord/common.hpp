#ifndef DISCORD_COMMON_HPP
#define DISCORD_COMMON_HPP

namespace tl::kt::discord
{    
    using opcode_t      = int;
    using sequence_t    = int;
    using event_name_t  = std::string;
    
    struct opcode
    {
        static constexpr opcode_t dispatch         = 0;
        static constexpr opcode_t heartbeat        = 1;
        static constexpr opcode_t identify         = 2;
        static constexpr opcode_t presence         = 3;
        static constexpr opcode_t voice            = 4;
        static constexpr opcode_t resume           = 6;
        static constexpr opcode_t reconnect        = 7;
        static constexpr opcode_t guild_members    = 8;
        static constexpr opcode_t invalid_session  = 9;
        static constexpr opcode_t hello            = 10;
        static constexpr opcode_t heartbeat_ack    = 11;
    };


}

#endif