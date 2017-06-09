#include "lvector2.h"
#include "lvector3.h"

LNAMESPACE_BEGIN

const LVector2 LVector2::up      =LVector2(0.0f,1.0f);
const LVector2 LVector2::down    =LVector2(0.0f,-1.0f);
const LVector2 LVector2::left    =LVector2(-1.0f,0.0f);
const LVector2 LVector2::right   =LVector2(1.0f,0.0f);
const LVector2 LVector2::zero    =LVector2(0.0f,0.0f);
const LVector2 LVector2::one     =LVector2(1.0f,1.0f);

LMatrix Lightning::LVector2::toTranslationMatrix() const
{
    return LMatrix::createTranslationMatrix(LVector3(x,y,0.0f));
}

LNAMESPACE_END
