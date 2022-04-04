#ifndef DISCORD_PAYLOAD_BASE_HPP
#define DISCORD_PAYLOAD_BASE_HPP

#include <tl/discord/common.hpp>
#include <nlohmann/json.hpp>

using json_t = nlohmann::json;

namespace tl::kt::discord
{

    class PayloadBase
    {

        private:

            opcode_t        m_Opcode;
            sequence_t      m_Sequence;
            event_name_t    m_EventName;
            json_t          m_EventData;

    };

}

#endif