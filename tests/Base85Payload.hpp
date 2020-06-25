#include <string_view>

#ifndef BASE85_PAYLOAD_HPP_
#define BASE85_PAYLOAD_HPP_

constexpr char const * const base85Payload =
    R"ascii85Text(9jqo^BlbD-BleB1DJ+*+F(f,q/0JhKF<GL>Cj@.4Gp$d7F!,L7@<6@)/0JDEF<G%<+EV:2F!,O<DJ+*.@<*K0@<6L(Df-\0Ec5e;DffZ(EZee.Bl.9pF"AGXBPCsi+DGm)ascii85Text"
    R"ascii85Text(>@3BB/F*&OCAfu2/AKYi(DIb:@FD,*)+C]U=@3BN#EcYf8ATD3s@q?d$AftVqCh[NqF<G:8+EV:.+Cf>-FD5W8ARlolDIal(DId<j@<?3r@:F%a+D58'ATD4$Bl@l3De:)ascii85Text"
    R"ascii85Text(,-DJs`8ARoFb/0JMK@qB4^F!,R<AKZ&-DfTqBG%G>uD.RTpAKYo'+CT/5+Cei#DII?(E,9)oF*2M7/c)ascii85Text";

constexpr char const * const base85PayloadWithSpaces =
    R"ascii85Text(9jq o^Blb D-BleB1DJ+*+F(f,q/0J hKF<GL>Cj  @.4Gp$d7F!,L7@<6@)
                  /0JDEF<G%<+EV:2F!,O<DJ+*.@<*K0@<6L (Df-\0E c5e;DffZ(EZee.Bl.9pF"AGXBPCsi+DGm)ascii85Text
                  >@3BB/F*&OCAfu2/AKYi(DIb:@FD,*)+C]U=@3BN#Ec   Yf8ATD3s@q  ?d$AftVqCh[NqF<G:8+EV:.+Cf>-FD5W8ARlolDIal(DId<j@<?3r@:F%a+D58'ATD4$Bl@l3De:)ascii85Text
                  ,-DJs`8ARoFb/0JMK@qB4^F!,R<AKZ&-DfTqBG%G>uD.RTpAKYo'+CT/5+ Cei#DII?(E,9)oF*2M7/c)ascii85Text";

constexpr char const * const realText =
    "Man is distinguished, not only by his reason, but by this singular passion from other animals, which "
    "is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge,"
    " exceeds the short vehemence of any carnal pleasure.";

#endif
