#include "lvector3.h"
#include "lvector4.h"
LNAMESPACE_BEGIN

const LVector3 LVector3::up      =LVector3(0.0f,1.0f,0.0f);
const LVector3 LVector3::down    =LVector3(0.0f,-1.0f,0.0f);
const LVector3 LVector3::left    =LVector3(-1.0f,0.0f,0.0f);
const LVector3 LVector3::right   =LVector3(1.0f,0.0f,0.0f);
const LVector3 LVector3::forward =LVector3(0.0f,0.0f,1.0f);
const LVector3 LVector3::back    =LVector3(0.0f,0.0f,-1.0f);
const LVector3 LVector3::zero    =LVector3(0.0f,0.0f,0.0f);
const LVector3 LVector3::one     =LVector3(1.0f,1.0f,1.0f);

LVector3::operator LVector4() const
{
    return LVector4((*this));
}


LNAMESPACE_END

