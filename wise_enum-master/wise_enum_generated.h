#define WISE_ENUM_IMPL_ARG_N(                                                           \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,                                            \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,                                   \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,                                   \
    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,                                   \
    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50,                                   \
    N, ...                                                                              \
  )                                                                                     \
  N                                                                                     \

#define WISE_ENUM_IMPL_RSEQ_N()                                                         \
  50, 49, 48, 47, 46, 45, 44, 43, 42, 41,                                               \
  40, 39, 38, 37, 36, 35, 34, 33, 32, 31,                                               \
  30, 29, 28, 27, 26, 25, 24, 23, 22, 21,                                               \
  20, 19, 18, 17, 16, 15, 14, 13, 12, 11,                                               \
  10, 9, 8, 7, 6, 5, 4, 3, 2, 1,                                                        \
  0                                                                                     \

#define WISE_ENUM_IMPL_LOOP_1(M, C, D, x) M(C, x)

#define WISE_ENUM_IMPL_LOOP_2(M, C, D, x, ...) M(C, x) D()                              \
  WISE_ENUM_IMPL_LOOP_1(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_3(M, C, D, x, ...) M(C, x) D()                              \
  WISE_ENUM_IMPL_LOOP_2(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_4(M, C, D, x, ...) M(C, x) D()                              \
  WISE_ENUM_IMPL_LOOP_3(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_5(M, C, D, x, ...) M(C, x) D()                              \
  WISE_ENUM_IMPL_LOOP_4(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_6(M, C, D, x, ...) M(C, x) D()                              \
  WISE_ENUM_IMPL_LOOP_5(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_7(M, C, D, x, ...) M(C, x) D()                              \
  WISE_ENUM_IMPL_LOOP_6(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_8(M, C, D, x, ...) M(C, x) D()                              \
  WISE_ENUM_IMPL_LOOP_7(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_9(M, C, D, x, ...) M(C, x) D()                              \
  WISE_ENUM_IMPL_LOOP_8(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_10(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_9(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_11(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_10(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_12(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_11(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_13(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_12(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_14(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_13(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_15(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_14(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_16(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_15(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_17(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_16(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_18(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_17(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_19(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_18(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_20(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_19(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_21(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_20(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_22(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_21(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_23(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_22(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_24(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_23(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_25(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_24(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_26(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_25(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_27(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_26(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_28(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_27(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_29(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_28(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_30(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_29(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_31(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_30(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_32(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_31(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_33(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_32(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_34(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_33(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_35(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_34(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_36(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_35(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_37(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_36(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_38(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_37(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_39(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_38(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_40(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_39(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_41(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_40(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_42(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_41(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_43(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_42(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_44(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_43(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_45(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_44(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_46(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_45(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_47(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_46(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_48(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_47(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_49(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_48(M, C, D, __VA_ARGS__)

#define WISE_ENUM_IMPL_LOOP_50(M, C, D, x, ...) M(C, x) D()                             \
  WISE_ENUM_IMPL_LOOP_49(M, C, D, __VA_ARGS__)

