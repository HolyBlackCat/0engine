#ifndef PREPROCESSOR_H_INCLUDED
#define PREPROCESSOR_H_INCLUDED

// Version 0.0.1 by HolyBlackCat

#define PP0_F_NULL()
#define PP0_F_COMMA() ,

#define PP0_E(...) __VA_ARGS__

#define PP0_VA_FIRST(...) PP0_VA_FIRST_IMPL_(__VA_ARGS__,)
#define PP0_VA_FIRST_IMPL_(x, ...) x

#define PP0_PARENS(...) (__VA_ARGS__)
#define PP0_DEL_PARENS(...) PP0_E __VA_ARGS__
#define PP0_2_PARENS(...) ((__VA_ARGS__))

#define PP0_CC(a, b) PP0_CC_IMPL_(a,b)
#define PP0_CC_IMPL_(a, b) a##b

#define PP0_CALL(macro, ...) macro(__VA_ARGS__)

#define PP0_VA_SIZE(...) PP0_VA_SIZE_IMPL_(__VA_ARGS__,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define PP0_VA_SIZE_IMPL_(i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,i61,i62,i63,i64,size,...) size

#define PP0_STR(...) PP0_STR_IMPL_(__VA_ARGS__)
#define PP0_STR_IMPL_(...) #__VA_ARGS__

#define PP0_VA_CALL(name, ...) PP0_CC(name, PP0_VA_SIZE(__VA_ARGS__))

#define PP0_SEQ_CALL(name, seq) PP0_CC(name, PP0_SEQ_SIZE(seq))

#define PP0_SEQ_TO_VA(seq) PP0_SEQ_APPLY(seq, PP0_E, PP0_F_COMMA)
#define PP0_SEQ_TO_VA_PARENS(seq) PP0_SEQ_APPLY(seq, PP0_PARENS, PP0_F_COMMA)
#define PP0_SEQ_EXPAND(seq) PP0_SEQ_APPLY(seq, PP0_E, PP0_F_NULL)
#define PP0_VA_EXPAND(seq) PP0_SEQ_APPLY(PP0_VA_TO_SEQ(seq), PP0_E, PP0_F_NULL)

#define PP0_SEQ_DEL_FIRST(seq) PP0_SEQ_DEL_FIRST_IMPL_ seq
#define PP0_SEQ_DEL_FIRST_IMPL_(...)

#define PP0_SEQ_FIRST(seq) PP0_DEL_PARENS(PP0_VA_FIRST(PP0_SEQ_FIRST_IMPL_ seq,))
#define PP0_SEQ_FIRST_IMPL_(...) (__VA_ARGS__),

#define PP0_VA_TO_SEQ(...) PP0_VA_CALL(PP0_VA_TO_SEQ_, __VA_ARGS__)(__VA_ARGS__)
#define PP0_VA_TO_SEQ_0() 
#define PP0_VA_TO_SEQ_1(i0) (i0)
#define PP0_VA_TO_SEQ_2(i0,i1) (i0)(i1)
#define PP0_VA_TO_SEQ_3(i0,i1,i2) (i0)(i1)(i2)
#define PP0_VA_TO_SEQ_4(i0,i1,i2,i3) (i0)(i1)(i2)(i3)
#define PP0_VA_TO_SEQ_5(i0,i1,i2,i3,i4) (i0)(i1)(i2)(i3)(i4)
#define PP0_VA_TO_SEQ_6(i0,i1,i2,i3,i4,i5) (i0)(i1)(i2)(i3)(i4)(i5)
#define PP0_VA_TO_SEQ_7(i0,i1,i2,i3,i4,i5,i6) (i0)(i1)(i2)(i3)(i4)(i5)(i6)
#define PP0_VA_TO_SEQ_8(i0,i1,i2,i3,i4,i5,i6,i7) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)
#define PP0_VA_TO_SEQ_9(i0,i1,i2,i3,i4,i5,i6,i7,i8) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)
#define PP0_VA_TO_SEQ_10(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)
#define PP0_VA_TO_SEQ_11(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)
#define PP0_VA_TO_SEQ_12(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)
#define PP0_VA_TO_SEQ_13(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)
#define PP0_VA_TO_SEQ_14(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)
#define PP0_VA_TO_SEQ_15(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)
#define PP0_VA_TO_SEQ_16(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)
#define PP0_VA_TO_SEQ_17(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)
#define PP0_VA_TO_SEQ_18(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)
#define PP0_VA_TO_SEQ_19(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)
#define PP0_VA_TO_SEQ_20(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)
#define PP0_VA_TO_SEQ_21(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)
#define PP0_VA_TO_SEQ_22(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)
#define PP0_VA_TO_SEQ_23(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)
#define PP0_VA_TO_SEQ_24(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)
#define PP0_VA_TO_SEQ_25(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)
#define PP0_VA_TO_SEQ_26(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)
#define PP0_VA_TO_SEQ_27(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)
#define PP0_VA_TO_SEQ_28(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)
#define PP0_VA_TO_SEQ_29(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)
#define PP0_VA_TO_SEQ_30(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)
#define PP0_VA_TO_SEQ_31(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)
#define PP0_VA_TO_SEQ_32(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)
#define PP0_VA_TO_SEQ_33(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)
#define PP0_VA_TO_SEQ_34(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)
#define PP0_VA_TO_SEQ_35(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)
#define PP0_VA_TO_SEQ_36(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)
#define PP0_VA_TO_SEQ_37(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)
#define PP0_VA_TO_SEQ_38(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)
#define PP0_VA_TO_SEQ_39(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)
#define PP0_VA_TO_SEQ_40(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)
#define PP0_VA_TO_SEQ_41(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)
#define PP0_VA_TO_SEQ_42(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)
#define PP0_VA_TO_SEQ_43(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)
#define PP0_VA_TO_SEQ_44(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)
#define PP0_VA_TO_SEQ_45(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)
#define PP0_VA_TO_SEQ_46(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)
#define PP0_VA_TO_SEQ_47(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)
#define PP0_VA_TO_SEQ_48(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)
#define PP0_VA_TO_SEQ_49(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)
#define PP0_VA_TO_SEQ_50(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)
#define PP0_VA_TO_SEQ_51(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)
#define PP0_VA_TO_SEQ_52(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)
#define PP0_VA_TO_SEQ_53(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)
#define PP0_VA_TO_SEQ_54(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)
#define PP0_VA_TO_SEQ_55(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)
#define PP0_VA_TO_SEQ_56(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)(i55)
#define PP0_VA_TO_SEQ_57(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)(i55)(i56)
#define PP0_VA_TO_SEQ_58(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)(i55)(i56)(i57)
#define PP0_VA_TO_SEQ_59(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)(i55)(i56)(i57)(i58)
#define PP0_VA_TO_SEQ_60(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)(i55)(i56)(i57)(i58)(i59)
#define PP0_VA_TO_SEQ_61(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)(i55)(i56)(i57)(i58)(i59)(i60)
#define PP0_VA_TO_SEQ_62(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,i61) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)(i55)(i56)(i57)(i58)(i59)(i60)(i61)
#define PP0_VA_TO_SEQ_63(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,i61,i62) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)(i55)(i56)(i57)(i58)(i59)(i60)(i61)(i62)
#define PP0_VA_TO_SEQ_64(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,i61,i62,i63) (i0)(i1)(i2)(i3)(i4)(i5)(i6)(i7)(i8)(i9)(i10)(i11)(i12)(i13)(i14)(i15)(i16)(i17)(i18)(i19)(i20)(i21)(i22)(i23)(i24)(i25)(i26)(i27)(i28)(i29)(i30)(i31)(i32)(i33)(i34)(i35)(i36)(i37)(i38)(i39)(i40)(i41)(i42)(i43)(i44)(i45)(i46)(i47)(i48)(i49)(i50)(i51)(i52)(i53)(i54)(i55)(i56)(i57)(i58)(i59)(i60)(i61)(i62)(i63)

#define PP0_SEQ_SIZE(seq) PP0_CC(PP0_SEQ_SIZE_0 seq, _VAL)
#define PP0_SEQ_SIZE_0(...) PP0_SEQ_SIZE_1
#define PP0_SEQ_SIZE_1(...) PP0_SEQ_SIZE_2
#define PP0_SEQ_SIZE_2(...) PP0_SEQ_SIZE_3
#define PP0_SEQ_SIZE_3(...) PP0_SEQ_SIZE_4
#define PP0_SEQ_SIZE_4(...) PP0_SEQ_SIZE_5
#define PP0_SEQ_SIZE_5(...) PP0_SEQ_SIZE_6
#define PP0_SEQ_SIZE_6(...) PP0_SEQ_SIZE_7
#define PP0_SEQ_SIZE_7(...) PP0_SEQ_SIZE_8
#define PP0_SEQ_SIZE_8(...) PP0_SEQ_SIZE_9
#define PP0_SEQ_SIZE_9(...) PP0_SEQ_SIZE_10
#define PP0_SEQ_SIZE_10(...) PP0_SEQ_SIZE_11
#define PP0_SEQ_SIZE_11(...) PP0_SEQ_SIZE_12
#define PP0_SEQ_SIZE_12(...) PP0_SEQ_SIZE_13
#define PP0_SEQ_SIZE_13(...) PP0_SEQ_SIZE_14
#define PP0_SEQ_SIZE_14(...) PP0_SEQ_SIZE_15
#define PP0_SEQ_SIZE_15(...) PP0_SEQ_SIZE_16
#define PP0_SEQ_SIZE_16(...) PP0_SEQ_SIZE_17
#define PP0_SEQ_SIZE_17(...) PP0_SEQ_SIZE_18
#define PP0_SEQ_SIZE_18(...) PP0_SEQ_SIZE_19
#define PP0_SEQ_SIZE_19(...) PP0_SEQ_SIZE_20
#define PP0_SEQ_SIZE_20(...) PP0_SEQ_SIZE_21
#define PP0_SEQ_SIZE_21(...) PP0_SEQ_SIZE_22
#define PP0_SEQ_SIZE_22(...) PP0_SEQ_SIZE_23
#define PP0_SEQ_SIZE_23(...) PP0_SEQ_SIZE_24
#define PP0_SEQ_SIZE_24(...) PP0_SEQ_SIZE_25
#define PP0_SEQ_SIZE_25(...) PP0_SEQ_SIZE_26
#define PP0_SEQ_SIZE_26(...) PP0_SEQ_SIZE_27
#define PP0_SEQ_SIZE_27(...) PP0_SEQ_SIZE_28
#define PP0_SEQ_SIZE_28(...) PP0_SEQ_SIZE_29
#define PP0_SEQ_SIZE_29(...) PP0_SEQ_SIZE_30
#define PP0_SEQ_SIZE_30(...) PP0_SEQ_SIZE_31
#define PP0_SEQ_SIZE_31(...) PP0_SEQ_SIZE_32
#define PP0_SEQ_SIZE_32(...) PP0_SEQ_SIZE_33
#define PP0_SEQ_SIZE_33(...) PP0_SEQ_SIZE_34
#define PP0_SEQ_SIZE_34(...) PP0_SEQ_SIZE_35
#define PP0_SEQ_SIZE_35(...) PP0_SEQ_SIZE_36
#define PP0_SEQ_SIZE_36(...) PP0_SEQ_SIZE_37
#define PP0_SEQ_SIZE_37(...) PP0_SEQ_SIZE_38
#define PP0_SEQ_SIZE_38(...) PP0_SEQ_SIZE_39
#define PP0_SEQ_SIZE_39(...) PP0_SEQ_SIZE_40
#define PP0_SEQ_SIZE_40(...) PP0_SEQ_SIZE_41
#define PP0_SEQ_SIZE_41(...) PP0_SEQ_SIZE_42
#define PP0_SEQ_SIZE_42(...) PP0_SEQ_SIZE_43
#define PP0_SEQ_SIZE_43(...) PP0_SEQ_SIZE_44
#define PP0_SEQ_SIZE_44(...) PP0_SEQ_SIZE_45
#define PP0_SEQ_SIZE_45(...) PP0_SEQ_SIZE_46
#define PP0_SEQ_SIZE_46(...) PP0_SEQ_SIZE_47
#define PP0_SEQ_SIZE_47(...) PP0_SEQ_SIZE_48
#define PP0_SEQ_SIZE_48(...) PP0_SEQ_SIZE_49
#define PP0_SEQ_SIZE_49(...) PP0_SEQ_SIZE_50
#define PP0_SEQ_SIZE_50(...) PP0_SEQ_SIZE_51
#define PP0_SEQ_SIZE_51(...) PP0_SEQ_SIZE_52
#define PP0_SEQ_SIZE_52(...) PP0_SEQ_SIZE_53
#define PP0_SEQ_SIZE_53(...) PP0_SEQ_SIZE_54
#define PP0_SEQ_SIZE_54(...) PP0_SEQ_SIZE_55
#define PP0_SEQ_SIZE_55(...) PP0_SEQ_SIZE_56
#define PP0_SEQ_SIZE_56(...) PP0_SEQ_SIZE_57
#define PP0_SEQ_SIZE_57(...) PP0_SEQ_SIZE_58
#define PP0_SEQ_SIZE_58(...) PP0_SEQ_SIZE_59
#define PP0_SEQ_SIZE_59(...) PP0_SEQ_SIZE_60
#define PP0_SEQ_SIZE_60(...) PP0_SEQ_SIZE_61
#define PP0_SEQ_SIZE_61(...) PP0_SEQ_SIZE_62
#define PP0_SEQ_SIZE_62(...) PP0_SEQ_SIZE_63
#define PP0_SEQ_SIZE_63(...) PP0_SEQ_SIZE_64
#define PP0_SEQ_SIZE_64(...) PP0_SEQ_SIZE_65
#define PP0_SEQ_SIZE_0_VAL 0
#define PP0_SEQ_SIZE_1_VAL 1
#define PP0_SEQ_SIZE_2_VAL 2
#define PP0_SEQ_SIZE_3_VAL 3
#define PP0_SEQ_SIZE_4_VAL 4
#define PP0_SEQ_SIZE_5_VAL 5
#define PP0_SEQ_SIZE_6_VAL 6
#define PP0_SEQ_SIZE_7_VAL 7
#define PP0_SEQ_SIZE_8_VAL 8
#define PP0_SEQ_SIZE_9_VAL 9
#define PP0_SEQ_SIZE_10_VAL 10
#define PP0_SEQ_SIZE_11_VAL 11
#define PP0_SEQ_SIZE_12_VAL 12
#define PP0_SEQ_SIZE_13_VAL 13
#define PP0_SEQ_SIZE_14_VAL 14
#define PP0_SEQ_SIZE_15_VAL 15
#define PP0_SEQ_SIZE_16_VAL 16
#define PP0_SEQ_SIZE_17_VAL 17
#define PP0_SEQ_SIZE_18_VAL 18
#define PP0_SEQ_SIZE_19_VAL 19
#define PP0_SEQ_SIZE_20_VAL 20
#define PP0_SEQ_SIZE_21_VAL 21
#define PP0_SEQ_SIZE_22_VAL 22
#define PP0_SEQ_SIZE_23_VAL 23
#define PP0_SEQ_SIZE_24_VAL 24
#define PP0_SEQ_SIZE_25_VAL 25
#define PP0_SEQ_SIZE_26_VAL 26
#define PP0_SEQ_SIZE_27_VAL 27
#define PP0_SEQ_SIZE_28_VAL 28
#define PP0_SEQ_SIZE_29_VAL 29
#define PP0_SEQ_SIZE_30_VAL 30
#define PP0_SEQ_SIZE_31_VAL 31
#define PP0_SEQ_SIZE_32_VAL 32
#define PP0_SEQ_SIZE_33_VAL 33
#define PP0_SEQ_SIZE_34_VAL 34
#define PP0_SEQ_SIZE_35_VAL 35
#define PP0_SEQ_SIZE_36_VAL 36
#define PP0_SEQ_SIZE_37_VAL 37
#define PP0_SEQ_SIZE_38_VAL 38
#define PP0_SEQ_SIZE_39_VAL 39
#define PP0_SEQ_SIZE_40_VAL 40
#define PP0_SEQ_SIZE_41_VAL 41
#define PP0_SEQ_SIZE_42_VAL 42
#define PP0_SEQ_SIZE_43_VAL 43
#define PP0_SEQ_SIZE_44_VAL 44
#define PP0_SEQ_SIZE_45_VAL 45
#define PP0_SEQ_SIZE_46_VAL 46
#define PP0_SEQ_SIZE_47_VAL 47
#define PP0_SEQ_SIZE_48_VAL 48
#define PP0_SEQ_SIZE_49_VAL 49
#define PP0_SEQ_SIZE_50_VAL 50
#define PP0_SEQ_SIZE_51_VAL 51
#define PP0_SEQ_SIZE_52_VAL 52
#define PP0_SEQ_SIZE_53_VAL 53
#define PP0_SEQ_SIZE_54_VAL 54
#define PP0_SEQ_SIZE_55_VAL 55
#define PP0_SEQ_SIZE_56_VAL 56
#define PP0_SEQ_SIZE_57_VAL 57
#define PP0_SEQ_SIZE_58_VAL 58
#define PP0_SEQ_SIZE_59_VAL 59
#define PP0_SEQ_SIZE_60_VAL 60
#define PP0_SEQ_SIZE_61_VAL 61
#define PP0_SEQ_SIZE_62_VAL 62
#define PP0_SEQ_SIZE_63_VAL 63
#define PP0_SEQ_SIZE_64_VAL 64

#define PP0_VA_AT(index, ...) PP0_CC(PP0_VA_AT_, index)(__VA_ARGS__,)
#define PP0_SEQ_AT(index, seq) PP0_DEL_PARENS(PP0_VA_AT(index, PP0_SEQ_APPLY(seq, PP0_PARENS, PP0_F_COMMA)))
#define PP0_VA_AT_0(ret, ...) ret
#define PP0_VA_AT_1(i0,ret, ...) ret
#define PP0_VA_AT_2(i0,i1,ret, ...) ret
#define PP0_VA_AT_3(i0,i1,i2,ret, ...) ret
#define PP0_VA_AT_4(i0,i1,i2,i3,ret, ...) ret
#define PP0_VA_AT_5(i0,i1,i2,i3,i4,ret, ...) ret
#define PP0_VA_AT_6(i0,i1,i2,i3,i4,i5,ret, ...) ret
#define PP0_VA_AT_7(i0,i1,i2,i3,i4,i5,i6,ret, ...) ret
#define PP0_VA_AT_8(i0,i1,i2,i3,i4,i5,i6,i7,ret, ...) ret
#define PP0_VA_AT_9(i0,i1,i2,i3,i4,i5,i6,i7,i8,ret, ...) ret
#define PP0_VA_AT_10(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,ret, ...) ret
#define PP0_VA_AT_11(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,ret, ...) ret
#define PP0_VA_AT_12(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,ret, ...) ret
#define PP0_VA_AT_13(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,ret, ...) ret
#define PP0_VA_AT_14(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,ret, ...) ret
#define PP0_VA_AT_15(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,ret, ...) ret
#define PP0_VA_AT_16(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,ret, ...) ret
#define PP0_VA_AT_17(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,ret, ...) ret
#define PP0_VA_AT_18(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,ret, ...) ret
#define PP0_VA_AT_19(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,ret, ...) ret
#define PP0_VA_AT_20(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,ret, ...) ret
#define PP0_VA_AT_21(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,ret, ...) ret
#define PP0_VA_AT_22(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,ret, ...) ret
#define PP0_VA_AT_23(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,ret, ...) ret
#define PP0_VA_AT_24(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,ret, ...) ret
#define PP0_VA_AT_25(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,ret, ...) ret
#define PP0_VA_AT_26(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,ret, ...) ret
#define PP0_VA_AT_27(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,ret, ...) ret
#define PP0_VA_AT_28(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,ret, ...) ret
#define PP0_VA_AT_29(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,ret, ...) ret
#define PP0_VA_AT_30(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,ret, ...) ret
#define PP0_VA_AT_31(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,ret, ...) ret
#define PP0_VA_AT_32(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,ret, ...) ret
#define PP0_VA_AT_33(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,ret, ...) ret
#define PP0_VA_AT_34(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,ret, ...) ret
#define PP0_VA_AT_35(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,ret, ...) ret
#define PP0_VA_AT_36(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,ret, ...) ret
#define PP0_VA_AT_37(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,ret, ...) ret
#define PP0_VA_AT_38(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,ret, ...) ret
#define PP0_VA_AT_39(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,ret, ...) ret
#define PP0_VA_AT_40(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,ret, ...) ret
#define PP0_VA_AT_41(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,ret, ...) ret
#define PP0_VA_AT_42(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,ret, ...) ret
#define PP0_VA_AT_43(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,ret, ...) ret
#define PP0_VA_AT_44(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,ret, ...) ret
#define PP0_VA_AT_45(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,ret, ...) ret
#define PP0_VA_AT_46(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,ret, ...) ret
#define PP0_VA_AT_47(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,ret, ...) ret
#define PP0_VA_AT_48(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,ret, ...) ret
#define PP0_VA_AT_49(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,ret, ...) ret
#define PP0_VA_AT_50(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,ret, ...) ret
#define PP0_VA_AT_51(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,ret, ...) ret
#define PP0_VA_AT_52(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,ret, ...) ret
#define PP0_VA_AT_53(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,ret, ...) ret
#define PP0_VA_AT_54(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,ret, ...) ret
#define PP0_VA_AT_55(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,ret, ...) ret
#define PP0_VA_AT_56(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,ret, ...) ret
#define PP0_VA_AT_57(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,ret, ...) ret
#define PP0_VA_AT_58(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,ret, ...) ret
#define PP0_VA_AT_59(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,ret, ...) ret
#define PP0_VA_AT_60(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,ret, ...) ret
#define PP0_VA_AT_61(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,ret, ...) ret
#define PP0_VA_AT_62(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,i61,ret, ...) ret
#define PP0_VA_AT_63(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,i61,i62,ret, ...) ret
#define PP0_VA_AT_64(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,i61,i62,i63,ret, ...) ret

// macro(i, element)
#define PP0_SEQ_APPLY(seq, macro, macro_sep_f) PP0_SEQ_CALL(PP0_SEQ_APPLY_, seq)(macro, macro_sep_f, seq, )
#define PP0_SEQ_APPLY_0(macro, macro_sep_f, seq, seq_)
#define PP0_SEQ_APPLY_1(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq))
#define PP0_SEQ_APPLY_2(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_3(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_4(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_5(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_6(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_7(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_8(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_9(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_10(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_11(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_12(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_13(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_14(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_15(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_16(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_17(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_18(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_19(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_20(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_21(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_22(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_23(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_24(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_25(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_26(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_27(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_28(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_29(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_30(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_31(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_32(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_33(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_34(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_35(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_36(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_37(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_38(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_39(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_40(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_41(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_42(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_43(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_44(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_45(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_46(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_47(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_48(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_49(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_50(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_51(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_52(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_53(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_54(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_55(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_56(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_57(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_58(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_59(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_60(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_61(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_62(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_63(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_64(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)


#endif
