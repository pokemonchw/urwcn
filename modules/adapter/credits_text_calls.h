#pragma once
#include "../../sdk/text_services.h"

namespace uwcn::adapter {
// The 24 semantic append calls in native 1244F0. No positions, row slots or
// cached page text are kept here. The two original standalone <br> calls remain.
// Evidence: docs/evidence/credits-disassembly.txt and credits-string-bytes.txt.
struct CreditsTextCall {
    std::uint32_t site;
    TextComponent component;
};
inline constexpr CreditsTextCall credits_text_calls[]{
    {0x12452F,TextComponent::credits_introduction_1},
    {0x12453B,TextComponent::credits_introduction_2},
    {0x124553,TextComponent::credits_alexander},
    {0x12455F,TextComponent::credits_andrew},
    {0x12456B,TextComponent::credits_artemis},
    {0x124577,TextComponent::credits_artemiy},
    {0x124583,TextComponent::credits_brian},
    {0x12458F,TextComponent::credits_flap},
    {0x12459B,TextComponent::credits_hamsolovski},
    {0x1245A7,TextComponent::credits_jeremy},
    {0x1245B3,TextComponent::credits_kerri},
    {0x1245BF,TextComponent::credits_kuu},
    {0x1245CB,TextComponent::credits_lani},
    {0x1245D7,TextComponent::credits_paulo},
    {0x1245E3,TextComponent::credits_plotinus},
    {0x1245EF,TextComponent::credits_rain},
    {0x1245FB,TextComponent::credits_scott},
    {0x124607,TextComponent::credits_shawn},
    {0x124613,TextComponent::credits_tommy},
    {0x12461F,TextComponent::credits_wickerman},
    {0x12462B,TextComponent::credits_countrymen_1},
    {0x124637,TextComponent::credits_countrymen_2},
    {0x124643,TextComponent::credits_photo_contributors},
    {0x12464F,TextComponent::credits_veterans}
};
}
