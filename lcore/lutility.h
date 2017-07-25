#ifndef LUTILITY_H
#define LUTILITY_H
#include "ldefines.h"
#include "typeinfo.h"

#if LTARGET==LTARGET_DEBUG
template <typename... A> linline void _lunused(A&&...) {}
//! Disable Unused parameter warning
#define         LUNUSED(IN) _lunused(IN)
#else
#define         LUNUSED(IN)
#endif

/*!
 * \def LOVERLOADED_MACRO : using to overload macros by argument count. max allowed argumentst is 30
 *
 * #define TEST1(A1)
 * #define TEST2(A1,A2)
 * #define TEST3(A1,A2,A3)
 *
 * and now you can easily overload this
 * #define TEST(...) LOVERLOADED_MACRO(TEST,__VA_ARGS__)
 */
#define LOVERLOADED_MACRO( _MACRONAME_ ,...) __MACRO( _MACRONAME_ , _COUNTARGS(__VA_ARGS__))(__VA_ARGS__)
#define _COUNTARGS(...) __COUNTARGS((__VA_ARGS__,1000,999,998,997,996,995,994,993,992,991,990,989,988,987,986,985,984,983,982,981,980,979,978,977,976,975,974,973,972,971,970,969,968,967,966,965,964,963,962,961,960,959,958,957,956,955,954,953,952,951,950,949,948,947,946,945,944,943,942,941,940,939,938,937,936,935,934,933,932,931,930,929,928,927,926,925,924,923,922,921,920,919,918,917,916,915,914,913,912,911,910,909,908,907,906,905,904,903,902,901,900,899,898,897,896,895,894,893,892,891,890,889,888,887,886,885,884,883,882,881,880,879,878,877,876,875,874,873,872,871,870,869,868,867,866,865,864,863,862,861,860,859,858,857,856,855,854,853,852,851,850,849,848,847,846,845,844,843,842,841,840,839,838,837,836,835,834,833,832,831,830,829,828,827,826,825,824,823,822,821,820,819,818,817,816,815,814,813,812,811,810,809,808,807,806,805,804,803,802,801,800,799,798,797,796,795,794,793,792,791,790,789,788,787,786,785,784,783,782,781,780,779,778,777,776,775,774,773,772,771,770,769,768,767,766,765,764,763,762,761,760,759,758,757,756,755,754,753,752,751,750,749,748,747,746,745,744,743,742,741,740,739,738,737,736,735,734,733,732,731,730,729,728,727,726,725,724,723,722,721,720,719,718,717,716,715,714,713,712,711,710,709,708,707,706,705,704,703,702,701,700,699,698,697,696,695,694,693,692,691,690,689,688,687,686,685,684,683,682,681,680,679,678,677,676,675,674,673,672,671,670,669,668,667,666,665,664,663,662,661,660,659,658,657,656,655,654,653,652,651,650,649,648,647,646,645,644,643,642,641,640,639,638,637,636,635,634,633,632,631,630,629,628,627,626,625,624,623,622,621,620,619,618,617,616,615,614,613,612,611,610,609,608,607,606,605,604,603,602,601,600,599,598,597,596,595,594,593,592,591,590,589,588,587,586,585,584,583,582,581,580,579,578,577,576,575,574,573,572,571,570,569,568,567,566,565,564,563,562,561,560,559,558,557,556,555,554,553,552,551,550,549,548,547,546,545,544,543,542,541,540,539,538,537,536,535,534,533,532,531,530,529,528,527,526,525,524,523,522,521,520,519,518,517,516,515,514,513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,494,493,492,491,490,489,488,487,486,485,484,483,482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,463,462,461,460,459,458,457,456,455,454,453,452,451,450,449,448,447,446,445,444,443,442,441,440,439,438,437,436,435,434,433,432,431,430,429,428,427,426,425,424,423,422,421,420,419,418,417,416,415,414,413,412,411,410,409,408,407,406,405,404,403,402,401,400,399,398,397,396,395,394,393,392,391,390,389,388,387,386,385,384,383,382,381,380,379,378,377,376,375,374,373,372,371,370,369,368,367,366,365,364,363,362,361,360,359,358,357,356,355,354,353,352,351,350,349,348,347,346,345,344,343,342,341,340,339,338,337,336,335,334,333,332,331,330,329,328,327,326,325,324,323,322,321,320,319,318,317,316,315,314,313,312,311,310,309,308,307,306,305,304,303,302,301,300,299,298,297,296,295,294,293,292,291,290,289,288,287,286,285,284,283,282,281,280,279,278,277,276,275,274,273,272,271,270,269,268,267,266,265,264,263,262,261,260,259,258,257,256,255,254,253,252,251,250,249,248,247,246,245,244,243,242,241,240,239,238,237,236,235,234,233,232,231,230,229,228,227,226,225,224,223,222,221,220,219,218,217,216,215,214,213,212,211,210,209,208,207,206,205,204,203,202,201,200,199,198,197,196,195,194,193,192,191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172,171,170,169,168,167,166,165,164,163,162,161,160,159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144,143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __COUNTARGS(ARG) ___COUNTARGS ARG
#define ___COUNTARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,_70,_71,_72,_73,_74,_75,_76,_77,_78,_79,_80,_81,_82,_83,_84,_85,_86,_87,_88,_89,_90,_91,_92,_93,_94,_95,_96,_97,_98,_99,_100,_101,_102,_103,_104,_105,_106,_107,_108,_109,_110,_111,_112,_113,_114,_115,_116,_117,_118,_119,_120,_121,_122,_123,_124,_125,_126,_127,_128,_129,_130,_131,_132,_133,_134,_135,_136,_137,_138,_139,_140,_141,_142,_143,_144,_145,_146,_147,_148,_149,_150,_151,_152,_153,_154,_155,_156,_157,_158,_159,_160,_161,_162,_163,_164,_165,_166,_167,_168,_169,_170,_171,_172,_173,_174,_175,_176,_177,_178,_179,_180,_181,_182,_183,_184,_185,_186,_187,_188,_189,_190,_191,_192,_193,_194,_195,_196,_197,_198,_199,_200,_201,_202,_203,_204,_205,_206,_207,_208,_209,_210,_211,_212,_213,_214,_215,_216,_217,_218,_219,_220,_221,_222,_223,_224,_225,_226,_227,_228,_229,_230,_231,_232,_233,_234,_235,_236,_237,_238,_239,_240,_241,_242,_243,_244,_245,_246,_247,_248,_249,_250,_251,_252,_253,_254,_255,_256,_257,_258,_259,_260,_261,_262,_263,_264,_265,_266,_267,_268,_269,_270,_271,_272,_273,_274,_275,_276,_277,_278,_279,_280,_281,_282,_283,_284,_285,_286,_287,_288,_289,_290,_291,_292,_293,_294,_295,_296,_297,_298,_299,_300,_301,_302,_303,_304,_305,_306,_307,_308,_309,_310,_311,_312,_313,_314,_315,_316,_317,_318,_319,_320,_321,_322,_323,_324,_325,_326,_327,_328,_329,_330,_331,_332,_333,_334,_335,_336,_337,_338,_339,_340,_341,_342,_343,_344,_345,_346,_347,_348,_349,_350,_351,_352,_353,_354,_355,_356,_357,_358,_359,_360,_361,_362,_363,_364,_365,_366,_367,_368,_369,_370,_371,_372,_373,_374,_375,_376,_377,_378,_379,_380,_381,_382,_383,_384,_385,_386,_387,_388,_389,_390,_391,_392,_393,_394,_395,_396,_397,_398,_399,_400,_401,_402,_403,_404,_405,_406,_407,_408,_409,_410,_411,_412,_413,_414,_415,_416,_417,_418,_419,_420,_421,_422,_423,_424,_425,_426,_427,_428,_429,_430,_431,_432,_433,_434,_435,_436,_437,_438,_439,_440,_441,_442,_443,_444,_445,_446,_447,_448,_449,_450,_451,_452,_453,_454,_455,_456,_457,_458,_459,_460,_461,_462,_463,_464,_465,_466,_467,_468,_469,_470,_471,_472,_473,_474,_475,_476,_477,_478,_479,_480,_481,_482,_483,_484,_485,_486,_487,_488,_489,_490,_491,_492,_493,_494,_495,_496,_497,_498,_499,_500,_501,_502,_503,_504,_505,_506,_507,_508,_509,_510,_511,_512,_513,_514,_515,_516,_517,_518,_519,_520,_521,_522,_523,_524,_525,_526,_527,_528,_529,_530,_531,_532,_533,_534,_535,_536,_537,_538,_539,_540,_541,_542,_543,_544,_545,_546,_547,_548,_549,_550,_551,_552,_553,_554,_555,_556,_557,_558,_559,_560,_561,_562,_563,_564,_565,_566,_567,_568,_569,_570,_571,_572,_573,_574,_575,_576,_577,_578,_579,_580,_581,_582,_583,_584,_585,_586,_587,_588,_589,_590,_591,_592,_593,_594,_595,_596,_597,_598,_599,_600,_601,_602,_603,_604,_605,_606,_607,_608,_609,_610,_611,_612,_613,_614,_615,_616,_617,_618,_619,_620,_621,_622,_623,_624,_625,_626,_627,_628,_629,_630,_631,_632,_633,_634,_635,_636,_637,_638,_639,_640,_641,_642,_643,_644,_645,_646,_647,_648,_649,_650,_651,_652,_653,_654,_655,_656,_657,_658,_659,_660,_661,_662,_663,_664,_665,_666,_667,_668,_669,_670,_671,_672,_673,_674,_675,_676,_677,_678,_679,_680,_681,_682,_683,_684,_685,_686,_687,_688,_689,_690,_691,_692,_693,_694,_695,_696,_697,_698,_699,_700,_701,_702,_703,_704,_705,_706,_707,_708,_709,_710,_711,_712,_713,_714,_715,_716,_717,_718,_719,_720,_721,_722,_723,_724,_725,_726,_727,_728,_729,_730,_731,_732,_733,_734,_735,_736,_737,_738,_739,_740,_741,_742,_743,_744,_745,_746,_747,_748,_749,_750,_751,_752,_753,_754,_755,_756,_757,_758,_759,_760,_761,_762,_763,_764,_765,_766,_767,_768,_769,_770,_771,_772,_773,_774,_775,_776,_777,_778,_779,_780,_781,_782,_783,_784,_785,_786,_787,_788,_789,_790,_791,_792,_793,_794,_795,_796,_797,_798,_799,_800,_801,_802,_803,_804,_805,_806,_807,_808,_809,_810,_811,_812,_813,_814,_815,_816,_817,_818,_819,_820,_821,_822,_823,_824,_825,_826,_827,_828,_829,_830,_831,_832,_833,_834,_835,_836,_837,_838,_839,_840,_841,_842,_843,_844,_845,_846,_847,_848,_849,_850,_851,_852,_853,_854,_855,_856,_857,_858,_859,_860,_861,_862,_863,_864,_865,_866,_867,_868,_869,_870,_871,_872,_873,_874,_875,_876,_877,_878,_879,_880,_881,_882,_883,_884,_885,_886,_887,_888,_889,_890,_891,_892,_893,_894,_895,_896,_897,_898,_899,_900,_901,_902,_903,_904,_905,_906,_907,_908,_909,_910,_911,_912,_913,_914,_915,_916,_917,_918,_919,_920,_921,_922,_923,_924,_925,_926,_927,_928,_929,_930,_931,_932,_933,_934,_935,_936,_937,_938,_939,_940,_941,_942,_943,_944,_945,_946,_947,_948,_949,_950,_951,_952,_953,_954,_955,_956,_957,_958,_959,_960,_961,_962,_963,_964,_965,_966,_967,_968,_969,_970,_971,_972,_973,_974,_975,_976,_977,_978,_979,_980,_981,_982,_983,_984,_985,_986,_987,_988,_989,_990,_991,_992,_993,_994,_995,_996,_997,_998,_999,_1000,N,...) N
#define __MACRO( name , number) __MACRO2( name , number )
#define __MACRO2( name , number ) __MACRO3( name , number )
#define __MACRO3( name , number ) name##number


#define LCAT( ... ) LOVERLOADED_MACRO(__LCAT,__VA_ARGS__)

#define __LCAT2(A,B) A##B
#define __LCAT3(A,B,C) A##B##C
#define __LCAT4(A,B,C,D) A##B##C##D
#define __LCAT5(A,B,C,D,E) A##B##C##D##E

#define LVAARGS(...) _COUNTARGS(__VA_ARGS__), __VA_ARGS__

#define LTO_STRING(X) ______TOSTRING1(#X)
#define ______TOSTRING1(X) X

#define LPAR_OPEN (
#define LPAR_CLOSE )
#define LCOMMA ,

////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 *
 * lCallOnStart use this for function that need to be called right on program start before every thing
 *
 * sample:
 *
 * void lCallOnStart()
 * {
 *     cout<<"Hello World"<<endl;
 * }
 *
 * note: function type can not be changed
 * note: function is not a real function ! so you can NOT call it (but there is secret way to do that :D)
 * note: you can define this function multiple times inside a file !
 *
 */
#define lCallOnStart() \
static  LCAT(____lcall__,__LINE__)();\
namespace {\
    struct LCAT(_____fake_type_,__LINE__)\
    {\
        LCAT(_____fake_type_,__LINE__)()\
        {\
            LCAT(____lcall__,__LINE__)();\
        }\
        static const LCAT(_____fake_type_,__LINE__) m;\
    };\
const LCAT(_____fake_type_,__LINE__) LCAT(_____fake_type_,__LINE__)::m;\
}\
static void LCAT(____lcall__,__LINE__)()


/*!
 *
 * lCallOnEnd use this for function that need to be called right on program exit.
 *
 * sample:
 *
 * void lCallOnEnd()
 * {
 *     cout<<"Good Bye World"<<endl;
 * }
 *
 * note: if program crash this function will not be called
 * note: function type can not be changed
 * note: function is not a real function ! so you can NOT call it (but there is secret way to do that :D)
 * note: you can define this function multiple times inside a file !
 *
 */
#define lCallOnEnd() \
static  LCAT(____lcall__,__LINE__)();\
namespace {\
    struct LCAT(_____fake_type_,__LINE__)\
    {\
        ~ LCAT(_____fake_type_,__LINE__)()\
        {\
            LCAT(____lcall__,__LINE__)();\
        }\
        static const LCAT(_____fake_type_,__LINE__) m;\
    };\
const LCAT(_____fake_type_,__LINE__) LCAT(_____fake_type_,__LINE__)::m;\
}\
static void LCAT(____lcall__,__LINE__)()

////////////////////////////////////////////////////////////////////////////////////////////////////

//! how to use
//! class Test
//! {
//!     LSINGLETON_CLASS(Test)
//!     Test(){}
//!     ~Test(){}
//! public:
//!     //...
//! };
//!
//! and
//!
//! Test::get() will returns singleton class
//!

#define LSINGLETON_CLASS(CLASSNAME)\
CLASSNAME(const CLASSNAME&);\
CLASSNAME(CLASSNAME&&);\
CLASSNAME& operator=(const CLASSNAME&);\
CLASSNAME& operator=(CLASSNAME&&);\
public:\
static CLASSNAME& get()\
{\
    static CLASSNAME o;\
    return o;\
}\
private:

////////////////////////////////////////////////////////////////////////////////////////////////////

//! create automatically enum to enum convertor function
//!
//! LENUM_CONVERTOR(EnumA,EnumB,
//!                 EnumAItem1,EnumBItem1, // means they are similiar
//!                 ...
//! example:
//!
//! enum TypeA
//! {
//!    TypeA_1=0,
//!    TypeA_2,
//!    TypeA_3,
//!    TypeA_4,
//!    TypeA_5,
//!    TypeA_6,
//! };
//! enum TypeB
//! {
//!    TypeB_6=0,
//!    TypeB_5,
//!    TypeB_4,
//!    TypeB_3,
//!    TypeB_2,
//!    TypeB_1,
//! };
//! LENUM_CONVERTOR(TypeA,TypeB,
//!                TypeA_1,TypeB_1,
//!                TypeA_2,TypeB_2,
//!                TypeA_3,TypeB_3,
//!                TypeA_4,TypeB_4,
//!                TypeA_5,TypeB_5,
//!                TypeA_6,TypeB_6)
//!
//! and
//!
//! to use convertors
//! cout<<fromTypeBToTypeA(TypeB_3)<<" "<<fromTypeAToTypeB(TypeA_3)<<endl;
//!
//! to set custom function names do this
//!
//! LENUM_CONVERTOR2(TypeA,TypeB,AtoB,BtoA,
//! TypeA_1,TypeB_1,....
//!
//! and to use
//!
//! cout<<AtoB(TypeA_3)<<" "<<BtoA(TypeB_3)<<endl;
//!

#define LENUM_CONVERTOR2(_TYPEA,_TYPEB,_TYPE_A_TO_B,_TYPE_B_TO_A,_A,_B,...)\
_TYPEB _TYPE_A_TO_B(_TYPEA _val){\
    switch(_val){\
       __LENUM_CONVERTOR_HELPER(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B, __VA_ARGS__ )\
       default:break;\
    }\
        return _A;\
    }

#define LENUM_CONVERTOR(_TYPEA,_TYPEB,...)\
    LENUM_CONVERTOR2(_TYPEA,_TYPEB,LCAT(from,_TYPEA,To,_TYPEB),LCAT(from,_TYPEB,To,_TYPEA),__VA_ARGS__)


#define __LENUM_CONVERTOR_HELPER(...) LOVERLOADED_MACRO(___LENUM_CONVERTOR_HELPER,__VA_ARGS__)

#define ___LENUM_CONVERTOR_HELPER5(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B)\
    case _A:\
        return _B;\
    default:break;\
    }\
        return _B;\
    }\
    _TYPEA _TYPE_B_TO_A(_TYPEB _val){\
    switch(_val){\
    case _B:\
        return _A;

#define ___LENUM_CONVERTOR_HELPER7(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER5(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER9(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER7(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER11(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER9(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER13(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER11(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER15(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER13(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER17(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER15(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER19(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER17(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER21(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER19(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER23(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER21(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER25(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER23(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER27(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER25(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER29(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER27(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER31(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER29(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER33(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER31(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER35(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER33(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER37(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER35(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER39(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER37(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER41(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER39(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER43(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER41(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER45(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER43(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER47(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER45(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER49(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER47(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER51(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER49(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER53(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER51(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER55(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER53(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER57(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER55(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER59(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER57(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER61(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER59(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER63(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER61(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER65(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER63(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER67(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER65(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER69(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER67(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER71(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER69(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER73(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER71(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER75(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER73(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER77(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER75(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER79(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER77(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER81(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER79(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER83(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER81(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER85(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER83(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER87(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER85(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER89(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER87(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER91(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER89(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER93(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER91(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER95(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER93(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER97(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER95(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER99(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER97(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER101(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER99(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER103(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER101(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER105(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER103(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER107(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER105(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER109(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER107(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER111(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER109(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\


#define ___LENUM_CONVERTOR_HELPER113(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER111(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER115(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER113(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER117(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER115(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER119(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER117(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER121(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER119(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER123(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER121(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER125(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER123(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER127(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER125(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER129(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER127(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER131(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER129(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER133(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER131(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER135(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER133(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER137(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER135(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER139(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER137(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER141(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER139(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER143(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER141(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER145(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER143(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER147(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER145(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER149(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER147(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER151(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER149(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER153(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER151(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER155(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER153(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER157(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER155(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER159(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER157(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER161(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER159(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER163(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER161(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER165(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER163(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER167(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER165(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER169(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER167(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER171(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER169(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER173(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER171(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER175(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER173(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER177(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER175(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER179(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER177(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER181(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER179(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER183(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER181(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER185(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER183(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER187(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER185(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER189(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER187(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER191(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER189(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER193(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER191(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER195(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER193(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER197(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER195(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER199(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER197(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\


#define ___LENUM_CONVERTOR_HELPER201(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER99(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER203(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER201(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER205(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER203(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER207(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER205(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER209(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER207(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER211(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER209(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\


#define ___LENUM_CONVERTOR_HELPER213(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER211(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER215(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER213(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER217(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER215(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER219(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER217(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER221(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER219(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER223(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER221(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER225(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER223(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER227(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER225(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER229(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER227(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER231(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER229(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER233(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER231(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER235(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER233(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER237(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER235(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER239(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER237(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER241(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER239(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER243(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER241(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER245(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER243(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER247(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER245(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER249(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER247(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER251(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER249(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER253(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER251(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER255(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER253(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER257(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER255(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER259(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER257(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER261(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER259(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER263(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER261(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER265(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER263(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER267(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER265(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER269(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER267(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER271(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER269(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER273(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER271(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER275(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER273(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER277(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER275(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER279(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER277(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER281(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER279(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER283(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER281(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER285(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER283(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER287(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER285(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER289(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER287(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER291(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER289(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER293(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER291(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER295(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER293(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER297(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER295(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER299(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
    case _A:\
        return _B;\
    ___LENUM_CONVERTOR_HELPER297(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
    case _B:\
        return _A;\

#define ___LENUM_CONVERTOR_HELPER301(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER299(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER303(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER301(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER305(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER303(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER307(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER305(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER309(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER307(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER311(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER309(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER313(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER311(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER315(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER313(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER317(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER315(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER319(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER317(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER321(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER319(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER323(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER321(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER325(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER323(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER327(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER325(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER329(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER327(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER331(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER329(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER333(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER331(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER335(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER333(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER337(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER335(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER339(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER337(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER341(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER339(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER343(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER341(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER345(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER343(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER347(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER345(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER349(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER347(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER351(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER349(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER353(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER351(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER355(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER353(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER357(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER355(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER359(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER357(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER361(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER359(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER363(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER361(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER365(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER363(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER367(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER365(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER369(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER367(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER371(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER369(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER373(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER371(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER375(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER373(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER377(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER375(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER379(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER377(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER381(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER379(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER383(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER381(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER385(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER383(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER387(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER385(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER389(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER387(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER391(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER389(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER393(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER391(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER395(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER393(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER397(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER395(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER399(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER397(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER401(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER399(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER403(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER401(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER405(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER403(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER407(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER405(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER409(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER407(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER411(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER409(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER413(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER411(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER415(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER413(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER417(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER415(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER419(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER417(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER421(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER419(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER423(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER421(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER425(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER423(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER427(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER425(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER429(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER427(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER431(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER429(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER433(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER431(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER435(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER433(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER437(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER435(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER439(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER437(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER441(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER439(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER443(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER441(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER445(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER443(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER447(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER445(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER449(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER447(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER451(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER449(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER453(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER451(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER455(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER453(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER457(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER455(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER459(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER457(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER461(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER459(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER463(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER461(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER465(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER463(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER467(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER465(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER469(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER467(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER471(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER469(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER473(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER471(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER475(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER473(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER477(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER475(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER479(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER477(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER481(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER479(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER483(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER481(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER485(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER483(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER487(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER485(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER489(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER487(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER491(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER489(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER493(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER491(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER495(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER493(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER497(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER495(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;

#define ___LENUM_CONVERTOR_HELPER499(_TYPEA,_TYPEB,_TYPE_B_TO_A,_A,_B,...)\
case _A:\
return _B;\
___LENUM_CONVERTOR_HELPER497(_TYPEA,_TYPEB,_TYPE_B_TO_A,__VA_ARGS__)\
case _B:\
return _A;




////////////////////////////////////////////////////////////////////////////////////////////////////
LNAMESPACE_BEGIN


//! remove reference & from type
template <typename T>
struct LRemoveReference
{
    typedef T type;
};
template <typename T>
struct LRemoveReference<T&>
{
    typedef T type;
};
template <typename T>
struct LRemoveReference<T&&>
{
    typedef T type;
};

//! remove pointer * from type
template <typename T>
struct LRemovePointer
{
    typedef T type;
};
template <typename T>
struct LRemovePointer<T*>
{
    typedef T type;
};
template <typename T>
struct LRemovePointer<T**>
{
    typedef T type;
};

template<typename T1,typename T2>
struct LIsSameType
{
    static const bool value=false;
};

template<typename T1>
struct LIsSameType<T1,T1>
{
    static const bool value=true;
};

//! check is A Derived from B .
//!
//!struct A
//!{
//!};
//!struct B:A
//!{
//!};
//!
//! cout<<lIsDerivedFrom<B,A>::value<<endl; // is true
//!
template <typename A, typename B>
struct LIsDerivedFrom
{
    template <typename _B, typename _A>
    struct ___ltest__
    {
        operator _B*() const;
        operator _A*();
    };
    struct yes{bool a[2];};
    struct no{bool a[1];};
    template <typename T>
    static yes check(A*,T);
    static no check(B*, int);
    static const bool value = LIsSameType<decltype(check(___ltest__<B,A>(), int())),yes>::value;
};

//! type is availble if first parameter was true
template<bool _con,typename T=void>
struct LEnable_If
{
};
template<typename T>
struct LEnable_If<true,T>
{
    typedef T type;
};

//! will returns a unique string for each value type
template<typename __T>
const char* lGetTypeName()
{
    return typeid(__T).name();
}

//! will returns a unique string for each value type
template<typename __T>
const char* lGetTypeName(__T in)
{
    LUNUSED(in);
    return typeid(__T).name();
}

template<typename T>
struct LIsPointer
{
    const static bool value=false;
};

template<typename T>
struct LIsPointer<T*>
{
    const static bool value=true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////


//! force to use move operator instead of copy operator
template<typename T>
linline typename LRemoveReference<T>::type&& lMove(T&& _in)
{
    return static_cast<typename LRemoveReference<T>::type&&>(_in);
}

//! Swap two value
template<typename T>
linline void    lSwap(T& _a,T& _b)
{
    T temp=lMove(_a);
    _a=lMove(_b);
    _b=lMove(temp);
}


//! to check some operators is availabe
//! example lHasOperator::Equal<int>::value is 1 because operator== is available for int
namespace LHasOperator
{
struct _No{bool _m[2];};
template<typename _T1, typename _T2>
inline _No operator== (const _T1&, const _T2&);
template<typename _T1, typename _T2>
inline _No operator!= (const _T1&, const _T2&);
template<typename _T1, typename _T2>
inline _No operator> (const _T1&, const _T2&);
template<typename _T1, typename _T2>
inline _No operator< (const _T1&, const _T2&);

template<typename T1, typename T2=T1>
struct Equal{ const static bool value = !LIsSameType<decltype( *(T1*)(0) == *(T2*)(0) ),_No>::value;};

template<typename T1, typename T2=T1>
struct NotEqual{ const static bool value = !LIsSameType<decltype( *(T1*)(0) != *(T2*)(0) ),_No>::value;};

template<typename T1, typename T2=T1>
struct Greater{ const static bool value = !LIsSameType<decltype( *(T1*)(0) > *(T2*)(0) ),_No>::value;};

template<typename T1, typename T2=T1>
struct Less{ const static bool value = !LIsSameType<decltype( *(T1*)(0) < *(T2*)(0) ),_No>::value;};
}

//! Checkout default constructor is availble or not
template <typename T>
struct LHasDefaultConstructor
{
    struct _No{bool _m[2];};

    template<typename U>
    static decltype(U(),bool()) is(u8);


    template<typename U>
    static _No is(...);

    const static bool value = !LIsSameType<decltype( is<T>(0) ),_No>::value;

};

////////////////////////////////////////////////////////////////////////////////////////////////////

enum LSortType
{
    LSortTypeAscending,
    LSortTypeDescending
};

template<typename T,typename ET>
linline u32 _qs_partitioninc(T& _arr,u32 left,u32 right)
{
    u32 l=left;
    u32 r=right-1;
    ET p=_arr[right];
    while(1)
    {
        while(_arr[l]<p)
            l++;
        while(r>0&&_arr[r]>p)
            r--;
        if(l>=r)
            break;
        else
            lSwap(_arr[l],_arr[r]);
    }
    lSwap(_arr[l],_arr[right]);
    return l;
}

template<typename T>
void lQuickSortInc(T& _arr,u32 _size,u32 left=0)
{
    if(left>=_size||_size<=1)
        return;
    int p=_qs_partitioninc<T,decltype(_arr[0])>(_arr,left,_size-1);
    lQuickSortInc(_arr,p,left);
    lQuickSortInc(_arr,_size,p+1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T,typename ET>
linline u32 _qs_partitiondec(T& _arr,u32 left,u32 right)
{
    u32 l=left;
    u32 r=right-1;
    ET p=_arr[right];
    while(1)
    {
        while(_arr[l]>p)
            l++;
        while(r>0&&_arr[r]<p)
            r--;
        if(l>=r)
            break;
        else
            lSwap(_arr[l],_arr[r]);
    }
    lSwap(_arr[l],_arr[right]);
    return l;
}

template<typename T>
void lQuickSortDec(T& _arr,u32 _size,u32 left=0)
{
    if(left>=_size||_size<=1)
        return;
    int p=_qs_partitiondec<T,decltype(_arr[0])>(_arr,left,_size-1);
    lQuickSortDec(_arr,p,left);
    lQuickSortDec(_arr,_size,p+1);
}



//! function to sort arrays
template<typename T>
void lSort(T& _arr,u32 _size,LSortType _type=LSortType::LSortTypeAscending)
{
    if(_type==LSortTypeAscending)
        lQuickSortInc(_arr,_size);
    else if(LSortTypeDescending)
        lQuickSortDec(_arr,_size);

}

LNAMESPACE_END

////////////////////////////////////////////////////////////////////////////////////////////////////





template<typename T>
struct ___fake_return{static T call(){T o;return o;}};
template<>
struct ___fake_return<void>{static void call(){}};

/*!
* how use call if exist.
* first define lConfigCallIfExist( checkID,Function_Return_Type,Function_Name, ARGUMENT_TYPES )
*
* then you can use it like this
* checkID<YourType>::value ; // if YourType has Function_Name with Function_Return_Type return type and ARGUMENT_TYPES argument types . then this will be true
* checkID<YourType>::call(your_object,arguments...);// this will call your_object.Function_Name(arguments...) if exist
*
* note : use lConfigCallIfExistConst instead for const functions
* sample:
*
* struct A
* {
*     void foo(int g)const{cout<<"FOO"<<endl;}
* };
* struct B
* {
*     void foo(int g)const{cout<<"FOO CONST"<<endl;}
* };
* struct C
* {
* };
*
* lConfigCallIfExist(has_foo,void,foo,int)
* lConfigCallIfExistConst(has_foo_const,void,foo,int)
*
* int main()
* {
*     A a;
*     B b;
*     C c;
*     int d;
*     has_foo<A>::call(a,3);// output FOO
*     has_foo<B>::call(b,4);
*     has_foo<C>::call(c,5);
*     has_foo<int>::call(d,6);

*     has_foo_const<A>::call(a,3);
*     has_foo_const<B>::call(b,4);// output FOOCONST
*     has_foo_const<C>::call(c,5);
*     has_foo_const<int>::call(d,6);
*
* }
*/
#define lConfigCallIfExist(...) LOVERLOADED_MACRO(__lConfigCallIfExist,__VA_ARGS__)
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist13(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist12(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8,a9);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8,a9);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist11(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist10(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist9(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){return __call(CT(),_in,a1,a2,a3,a4,a5,a6);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist8(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){return _in.FUNCNAME(a1,a2,a3,a4,a5);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){return __call(CT(),_in,a1,a2,a3,a4,a5);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist7(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4){return _in.FUNCNAME(a1,a2,a3,a4);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4){return __call(CT(),_in,a1,a2,a3,a4);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist6(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3){return _in.FUNCNAME(a1,a2,a3);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3){return __call(CT(),_in,a1,a2,a3);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist5(NAME,RETURNTYPE,FUNCNAME,A1,A2)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2){return _in.FUNCNAME(a1,a2);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2){return __call(CT(),_in,a1,a2);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist4(NAME,RETURNTYPE,FUNCNAME,A1)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1)>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1){return _in.FUNCNAME(a1);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1){return __call(CT(),_in,a1);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExist3(NAME,RETURNTYPE,FUNCNAME)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)()>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in){return _in.FUNCNAME();}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in){return __call(CT(),_in);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define lConfigCallIfExistConst(...) LOVERLOADED_MACRO(__lConfigCallIfExistConst,__VA_ARGS__)
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst13(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9,A10)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9,A10 a10){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst12(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8,A9)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8,A9)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8,a9);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8,a9);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst11(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7,A8)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7,A8)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7,a8);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7,a8);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst10(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6,A7)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6,A7)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6,a7);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7){return __call(CT(),_in,a1,a2,a3,a4,a5,a6,a7);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst9(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5,A6)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5,A6)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){return _in.FUNCNAME(a1,a2,a3,a4,a5,a6);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6){return __call(CT(),_in,a1,a2,a3,a4,a5,a6);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst8(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4,A5)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4,A5)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){return _in.FUNCNAME(a1,a2,a3,a4,a5);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5){return __call(CT(),_in,a1,a2,a3,a4,a5);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst7(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3,A4)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3,A4)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3,A4 a4){return _in.FUNCNAME(a1,a2,a3,a4);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3,A4 a4){return __call(CT(),_in,a1,a2,a3,a4);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst6(NAME,RETURNTYPE,FUNCNAME,A1,A2,A3)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2,A3)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2,A3 a3){return _in.FUNCNAME(a1,a2,a3);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2,A3 a3){return __call(CT(),_in,a1,a2,a3);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst5(NAME,RETURNTYPE,FUNCNAME,A1,A2)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1,A2)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1,A2 a2){return _in.FUNCNAME(a1,a2);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1,A2 a2){return __call(CT(),_in,a1,a2);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst4(NAME,RETURNTYPE,FUNCNAME,A1)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)(A1)const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in,A1 a1){return _in.FUNCNAME(a1);}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in,A1 a1){return __call(CT(),_in,a1);}\
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define __lConfigCallIfExistConst3(NAME,RETURNTYPE,FUNCNAME)\
template<typename T>\
struct NAME\
{\
    struct ___yes{bool b[1];};\
    struct ___no{bool b[2];};\
    template <typename U>\
    static ___yes check(decltype(static_cast<RETURNTYPE(U::*)()const>(&U::FUNCNAME)),void *);\
    template<typename U>\
    static ___no check(...);\
    const static bool value=LIsSameType<___yes,decltype(check<T>(0,0))>::value;\
\
    typedef decltype(check<T>(0,0)) CT;\
    template <typename U>static RETURNTYPE __call(const ___yes,U& _in){return _in.FUNCNAME();}\
    static RETURNTYPE __call(const ___no,...){return ___fake_return<RETURNTYPE>::call();}\
    static RETURNTYPE call(T& _in){return __call(CT(),_in);}\
};

#endif // LUTILITY_H
