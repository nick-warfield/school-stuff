/*
** Automatically generated from `sorting.m'
** by the Mercury compiler,
** version 14.01.1, configured for x86_64-unknown-linux-gnu.
** Do not edit.
**
** The autoconfigured grade settings governing
** the generation of this C file were
**
** TAG_BITS=3
** UNBOXED_FLOAT=yes
** PREGENERATED_DIST=no
** HIGHLEVEL_CODE=no
**
** END_OF_C_GRADE_INFO
*/

/*
INIT mercury__sorting__init
ENDINIT
*/

#define MR_ALLOW_RESET
#include "mercury_imp.h"
#line 140 "/usr/lib/mercury/ints/io.int2"
#include "io.mh"

#line 29 "sorting.c"
#line 150 "/usr/lib/mercury/ints/io.int2"
#include "time.mh"

#line 33 "sorting.c"
#line 151 "/usr/lib/mercury/ints/io.int2"
#include "string.mh"

#line 37 "sorting.c"
#line 31 "/usr/lib/mercury/ints/bitmap.int2"
#include "bitmap.mh"

#line 41 "sorting.c"
#line 33 "/usr/lib/mercury/ints/array.int2"
#include "array.mh"

#line 45 "sorting.c"
#line 46 "sorting.c"
#include "sorting.mh"

#line 49 "sorting.c"
#line 50 "sorting.c"
#ifndef SORTING_DECL_GUARD
#define SORTING_DECL_GUARD

#line 54 "sorting.c"
#line 55 "sorting.c"

#endif
#line 58 "sorting.c"

#ifdef _MSC_VER
#define MR_STATIC_LINKAGE extern
#else
#define MR_STATIC_LINKAGE static
#endif
MR_decl_label3(sorting__insert_sorted_3_0, 3,6,5)
MR_decl_label2(sorting__insertion_sort_3_0, 4,12)
MR_decl_label10(sorting__merge_sort_3_0, 5,6,8,9,3,17,18,55,14,22)
MR_decl_label8(sorting__merge_sort_3_0, 23,24,25,26,27,28,29,57)
MR_decl_label5(sorting__quick_sort_2_0, 18,4,5,6,8)
MR_decl_label4(sorting__quick_sort_helper_4_0, 23,5,4,7)
MR_def_extern_entry(sorting__insertion_sort_2_0)
MR_def_extern_entry(sorting__merge_sort_2_0)
MR_def_extern_entry(sorting__quick_sort_2_0)
MR_decl_static(sorting__insert_sorted_3_0)
MR_decl_static(sorting__insertion_sort_3_0)
MR_decl_static(sorting__merge_sort_3_0)
MR_decl_static(sorting__quick_sort_helper_4_0)




MR_BEGIN_MODULE(sorting_module0)
	MR_init_entry1(sorting__insertion_sort_2_0);
	MR_INIT_PROC_LAYOUT_ADDR(mercury__sorting__insertion_sort_2_0);
MR_BEGIN_CODE

/*-------------------------------------------------------------------------*/
/* code for 'insertion_sort'/2 mode 0 */
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_local_thread_engine_base
#endif
MR_define_entry(mercury__sorting__insertion_sort_2_0);
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_r1;
	MR_r1 = (MR_Word) MR_tbmkword(0, 0);
	MR_r2 = MR_tempr1;
	MR_np_tailcall_ent(sorting__insertion_sort_3_0);
	}
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_thread_engine_base
#endif
MR_END_MODULE


MR_BEGIN_MODULE(sorting_module1)
	MR_init_entry1(sorting__merge_sort_2_0);
	MR_INIT_PROC_LAYOUT_ADDR(mercury__sorting__merge_sort_2_0);
MR_BEGIN_CODE

/*-------------------------------------------------------------------------*/
/* code for 'merge_sort'/2 mode 0 */
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_local_thread_engine_base
#endif
MR_define_entry(mercury__sorting__merge_sort_2_0);
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_r1;
	MR_r1 = (MR_Word) MR_tbmkword(0, 0);
	MR_r2 = MR_tempr1;
	MR_np_tailcall_ent(sorting__merge_sort_3_0);
	}
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_thread_engine_base
#endif
MR_END_MODULE

extern const MR_TypeCtorInfo_Struct mercury_data_builtin__type_ctor_info_int_0;
MR_decl_entry(fn__list__append_2_0);

MR_BEGIN_MODULE(sorting_module2)
	MR_init_entry1(sorting__quick_sort_2_0);
	MR_INIT_PROC_LAYOUT_ADDR(mercury__sorting__quick_sort_2_0);
	MR_init_label5(sorting__quick_sort_2_0,18,4,5,6,8)
MR_BEGIN_CODE

/*-------------------------------------------------------------------------*/
/* code for 'quick_sort'/2 mode 0 */
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_local_thread_engine_base
#endif
MR_define_entry(mercury__sorting__quick_sort_2_0);
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	if (MR_LTAGS_TESTR(MR_r1,0,0)) {
		MR_GOTO_LAB(sorting__quick_sort_2_0_i18);
	}
	MR_r1 = (MR_Word) MR_tbmkword(0, 0);
	MR_proceed();
MR_def_label(sorting__quick_sort_2_0,18)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_incr_sp(3);
	MR_sv(3) = (MR_Word) MR_succip;
	MR_sv(1) = MR_tfield(1, MR_r1, 0);
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_r1;
	MR_r1 = MR_sv(1);
	MR_r2 = MR_tfield(1, MR_tempr1, 1);
	}
	MR_np_call_localret_ent(sorting__quick_sort_helper_4_0,
		sorting__quick_sort_2_0_i4);
MR_def_label(sorting__quick_sort_2_0,4)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_sv(2) = MR_r2;
	MR_np_localcall_lab(sorting__quick_sort_2_0,
		sorting__quick_sort_2_0_i5);
MR_def_label(sorting__quick_sort_2_0,5)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_r2 = MR_sv(2);
	MR_sv(2) = MR_r1;
	MR_r1 = MR_r2;
	MR_np_localcall_lab(sorting__quick_sort_2_0,
		sorting__quick_sort_2_0_i6);
MR_def_label(sorting__quick_sort_2_0,6)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1, MR_tempr2;
	MR_tag_alloc_heap(MR_tempr1, 1, (MR_Integer) 2);
	MR_r3 = MR_tempr1;
	MR_tfield(1, MR_tempr1, 0) = MR_sv(1);
	MR_tfield(1, MR_tempr1, 1) = (MR_Word) MR_tbmkword(0, 0);
	MR_sv(1) = MR_r1;
	MR_tempr2 = MR_sv(2);
	MR_sv(2) = (MR_Word) MR_INT_CTOR_ADDR;
	MR_r1 = MR_sv(2);
	MR_r2 = MR_tempr2;
	}
	MR_np_call_localret_ent(fn__list__append_2_0,
		sorting__quick_sort_2_0_i8);
MR_def_label(sorting__quick_sort_2_0,8)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_r1;
	MR_r1 = MR_sv(2);
	MR_r2 = MR_tempr1;
	MR_r3 = MR_sv(1);
	MR_succip_word = MR_sv(3);
	MR_decr_sp(3);
	MR_np_tailcall_ent(fn__list__append_2_0);
	}
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_thread_engine_base
#endif
MR_END_MODULE


MR_BEGIN_MODULE(sorting_module3)
	MR_init_entry1(sorting__insert_sorted_3_0);
	MR_INIT_PROC_LAYOUT_ADDR(mercury__sorting__insert_sorted_3_0);
	MR_init_label3(sorting__insert_sorted_3_0,3,6,5)
MR_BEGIN_CODE

/*-------------------------------------------------------------------------*/
/* code for 'insert_sorted'/3 mode 0 */
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_local_thread_engine_base
#endif
MR_def_static(sorting__insert_sorted_3_0)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	if (MR_LTAGS_TESTR(MR_r1,0,0)) {
		MR_GOTO_LAB(sorting__insert_sorted_3_0_i3);
	}
	MR_tag_alloc_heap(MR_r1, 1, (MR_Integer) 2);
	MR_tfield(1, MR_r1, 0) = MR_r2;
	MR_tfield(1, MR_r1, 1) = (MR_Word) MR_tbmkword(0, 0);
	MR_proceed();
MR_def_label(sorting__insert_sorted_3_0,3)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_tfield(1, MR_r1, 0);
	if (((MR_Integer) MR_r2 <= (MR_Integer) MR_tempr1)) {
		MR_GOTO_LAB(sorting__insert_sorted_3_0_i5);
	}
	MR_incr_sp(2);
	MR_sv(2) = (MR_Word) MR_succip;
	MR_sv(1) = MR_tempr1;
	MR_r1 = MR_tfield(1, MR_r1, 1);
	}
	MR_np_localcall_lab(sorting__insert_sorted_3_0,
		sorting__insert_sorted_3_0_i6);
MR_def_label(sorting__insert_sorted_3_0,6)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_tag_alloc_heap(MR_r2, 1, (MR_Integer) 2);
	MR_tfield(1, MR_r2, 0) = MR_sv(1);
	MR_tfield(1, MR_r2, 1) = MR_r1;
	MR_r1 = MR_r2;
	MR_decr_sp_and_return(2);
MR_def_label(sorting__insert_sorted_3_0,5)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tag_alloc_heap(MR_tempr1, 1, (MR_Integer) 2);
	MR_tfield(1, MR_tempr1, 0) = MR_r2;
	MR_tfield(1, MR_tempr1, 1) = MR_r1;
	MR_r1 = MR_tempr1;
	MR_proceed();
	}
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_thread_engine_base
#endif
MR_END_MODULE


MR_BEGIN_MODULE(sorting_module4)
	MR_init_entry1(sorting__insertion_sort_3_0);
	MR_INIT_PROC_LAYOUT_ADDR(mercury__sorting__insertion_sort_3_0);
	MR_init_label2(sorting__insertion_sort_3_0,4,12)
MR_BEGIN_CODE

/*-------------------------------------------------------------------------*/
/* code for 'insertion_sort'/3 mode 0 */
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_local_thread_engine_base
#endif
MR_def_static(sorting__insertion_sort_3_0)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_incr_sp(2);
	MR_sv(2) = (MR_Word) MR_succip;
	if (MR_LTAGS_TEST(MR_r2,0,0)) {
		MR_GOTO_LAB(sorting__insertion_sort_3_0_i12);
	}
	MR_sv(1) = MR_tfield(1, MR_r2, 1);
	MR_r2 = MR_tfield(1, MR_r2, 0);
	MR_np_call_localret_ent(sorting__insert_sorted_3_0,
		sorting__insertion_sort_3_0_i4);
MR_def_label(sorting__insertion_sort_3_0,4)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_r2 = MR_sv(1);
	MR_succip_word = MR_sv(2);
	if (MR_LTAGS_TEST(MR_r2,0,0)) {
		MR_GOTO_LAB(sorting__insertion_sort_3_0_i12);
	}
	MR_sv(1) = MR_tfield(1, MR_r2, 1);
	MR_r2 = MR_tfield(1, MR_r2, 0);
	MR_np_call_localret_ent(sorting__insert_sorted_3_0,
		sorting__insertion_sort_3_0_i4);
MR_def_label(sorting__insertion_sort_3_0,12)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_decr_sp_and_return(2);
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_thread_engine_base
#endif
MR_END_MODULE

MR_decl_entry(fn__list__length_1_0);
MR_decl_entry(fn__f_105_110_116_95_95_47_2_0);
MR_decl_entry(list__det_split_list_4_0);
MR_decl_entry(fn__list__merge_2_0);

MR_BEGIN_MODULE(sorting_module5)
	MR_init_entry1(sorting__merge_sort_3_0);
	MR_INIT_PROC_LAYOUT_ADDR(mercury__sorting__merge_sort_3_0);
	MR_init_label10(sorting__merge_sort_3_0,5,6,8,9,3,17,18,55,14,22)
	MR_init_label8(sorting__merge_sort_3_0,23,24,25,26,27,28,29,57)
MR_BEGIN_CODE

/*-------------------------------------------------------------------------*/
/* code for 'merge_sort'/3 mode 0 */
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_local_thread_engine_base
#endif
MR_def_static(sorting__merge_sort_3_0)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_incr_sp(4);
	MR_sv(4) = (MR_Word) MR_succip;
	if (MR_LTAGS_TESTR(MR_r1,0,0)) {
		MR_GOTO_LAB(sorting__merge_sort_3_0_i3);
	}
	if (MR_LTAGS_TESTR(MR_r2,0,0)) {
		MR_GOTO_LAB(sorting__merge_sort_3_0_i5);
	}
	MR_r1 = (MR_Word) MR_tbmkword(0, 0);
	MR_decr_sp_and_return(4);
MR_def_label(sorting__merge_sort_3_0,5)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_tfield(1, MR_r2, 1);
	if (MR_LTAGS_TESTR(MR_tempr1,0,0)) {
		MR_GOTO_LAB(sorting__merge_sort_3_0_i6);
	}
	MR_r1 = MR_r2;
	MR_decr_sp_and_return(4);
	}
MR_def_label(sorting__merge_sort_3_0,6)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_sv(1) = MR_r2;
	MR_sv(2) = (MR_Word) MR_INT_CTOR_ADDR;
	MR_r1 = MR_sv(2);
	MR_np_call_localret_ent(fn__list__length_1_0,
		sorting__merge_sort_3_0_i8);
MR_def_label(sorting__merge_sort_3_0,8)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_r2 = (MR_Integer) 2;
	MR_np_call_localret_ent(fn__f_105_110_116_95_95_47_2_0,
		sorting__merge_sort_3_0_i9);
MR_def_label(sorting__merge_sort_3_0,9)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_r1;
	MR_r1 = MR_sv(2);
	MR_r2 = MR_tempr1;
	MR_r3 = MR_sv(1);
	}
	MR_np_call_localret_ent(list__det_split_list_4_0,
		sorting__merge_sort_3_0_i55);
MR_def_label(sorting__merge_sort_3_0,3)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	if (MR_LTAGS_TESTR(MR_r2,0,0)) {
		MR_GOTO_LAB(sorting__merge_sort_3_0_i14);
	}
	MR_r2 = MR_tfield(1, MR_r1, 1);
	if (MR_LTAGS_TEST(MR_r2,0,0)) {
		MR_GOTO_LAB(sorting__merge_sort_3_0_i57);
	}
	MR_sv(2) = MR_r1;
	MR_sv(1) = (MR_Word) MR_INT_CTOR_ADDR;
	MR_r1 = MR_sv(1);
	MR_r2 = MR_sv(2);
	MR_np_call_localret_ent(fn__list__length_1_0,
		sorting__merge_sort_3_0_i17);
MR_def_label(sorting__merge_sort_3_0,17)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_r2 = (MR_Integer) 2;
	MR_np_call_localret_ent(fn__f_105_110_116_95_95_47_2_0,
		sorting__merge_sort_3_0_i18);
MR_def_label(sorting__merge_sort_3_0,18)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_r1;
	MR_r1 = MR_sv(1);
	MR_r2 = MR_tempr1;
	MR_r3 = MR_sv(2);
	}
	MR_np_call_localret_ent(list__det_split_list_4_0,
		sorting__merge_sort_3_0_i55);
MR_def_label(sorting__merge_sort_3_0,55)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_succip_word = MR_sv(4);
	if (MR_LTAGS_TESTR(MR_r1,0,0)) {
		MR_GOTO_LAB(sorting__merge_sort_3_0_i3);
	}
	if (MR_LTAGS_TESTR(MR_r2,0,0)) {
		MR_GOTO_LAB(sorting__merge_sort_3_0_i5);
	}
	MR_r1 = (MR_Word) MR_tbmkword(0, 0);
	MR_decr_sp_and_return(4);
MR_def_label(sorting__merge_sort_3_0,14)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_sv(2) = MR_r1;
	MR_sv(1) = MR_r2;
	MR_sv(3) = (MR_Word) MR_INT_CTOR_ADDR;
	MR_r1 = MR_sv(3);
	MR_r2 = MR_sv(2);
	MR_np_call_localret_ent(fn__list__length_1_0,
		sorting__merge_sort_3_0_i22);
MR_def_label(sorting__merge_sort_3_0,22)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_r2 = (MR_Integer) 2;
	MR_np_call_localret_ent(fn__f_105_110_116_95_95_47_2_0,
		sorting__merge_sort_3_0_i23);
MR_def_label(sorting__merge_sort_3_0,23)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_r1;
	MR_r1 = MR_sv(3);
	MR_r2 = MR_tempr1;
	MR_r3 = MR_sv(2);
	}
	MR_np_call_localret_ent(list__det_split_list_4_0,
		sorting__merge_sort_3_0_i24);
MR_def_label(sorting__merge_sort_3_0,24)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_np_localcall_lab(sorting__merge_sort_3_0,
		sorting__merge_sort_3_0_i25);
MR_def_label(sorting__merge_sort_3_0,25)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_sv(2) = MR_r1;
	MR_r1 = MR_sv(3);
	MR_r2 = MR_sv(1);
	MR_np_call_localret_ent(fn__list__length_1_0,
		sorting__merge_sort_3_0_i26);
MR_def_label(sorting__merge_sort_3_0,26)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_r2 = (MR_Integer) 2;
	MR_np_call_localret_ent(fn__f_105_110_116_95_95_47_2_0,
		sorting__merge_sort_3_0_i27);
MR_def_label(sorting__merge_sort_3_0,27)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_r1;
	MR_r1 = MR_sv(3);
	MR_r2 = MR_tempr1;
	MR_r3 = MR_sv(1);
	}
	MR_np_call_localret_ent(list__det_split_list_4_0,
		sorting__merge_sort_3_0_i28);
MR_def_label(sorting__merge_sort_3_0,28)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_np_localcall_lab(sorting__merge_sort_3_0,
		sorting__merge_sort_3_0_i29);
MR_def_label(sorting__merge_sort_3_0,29)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tempr1 = MR_r1;
	MR_r1 = MR_sv(3);
	MR_r2 = MR_sv(2);
	MR_r3 = MR_tempr1;
	MR_succip_word = MR_sv(4);
	MR_decr_sp(4);
	MR_np_tailcall_ent(fn__list__merge_2_0);
	}
MR_def_label(sorting__merge_sort_3_0,57)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_decr_sp_and_return(4);
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_thread_engine_base
#endif
MR_END_MODULE


MR_BEGIN_MODULE(sorting_module6)
	MR_init_entry1(sorting__quick_sort_helper_4_0);
	MR_INIT_PROC_LAYOUT_ADDR(mercury__sorting__quick_sort_helper_4_0);
	MR_init_label4(sorting__quick_sort_helper_4_0,23,5,4,7)
MR_BEGIN_CODE

/*-------------------------------------------------------------------------*/
/* code for 'quick_sort_helper'/4 mode 0 */
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_local_thread_engine_base
#endif
MR_def_static(sorting__quick_sort_helper_4_0)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	if (MR_LTAGS_TESTR(MR_r2,0,0)) {
		MR_GOTO_LAB(sorting__quick_sort_helper_4_0_i23);
	}
	MR_r1 = (MR_Word) MR_tbmkword(0, 0);
	MR_r2 = (MR_Word) MR_tbmkword(0, 0);
	MR_proceed();
MR_def_label(sorting__quick_sort_helper_4_0,23)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_incr_sp(2);
	MR_sv(2) = (MR_Word) MR_succip;
	MR_r3 = MR_tfield(1, MR_r2, 1);
	MR_sv(1) = MR_tfield(1, MR_r2, 0);
	if (((MR_Integer) MR_sv(1) >= (MR_Integer) MR_r1)) {
		MR_GOTO_LAB(sorting__quick_sort_helper_4_0_i4);
	}
	MR_r2 = MR_r3;
	MR_np_localcall_lab(sorting__quick_sort_helper_4_0,
		sorting__quick_sort_helper_4_0_i5);
MR_def_label(sorting__quick_sort_helper_4_0,5)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tag_alloc_heap(MR_tempr1, 1, (MR_Integer) 2);
	MR_tfield(1, MR_tempr1, 0) = MR_sv(1);
	MR_tfield(1, MR_tempr1, 1) = MR_r1;
	MR_r1 = MR_tempr1;
	MR_decr_sp_and_return(2);
	}
MR_def_label(sorting__quick_sort_helper_4_0,4)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	MR_r2 = MR_r3;
	MR_np_localcall_lab(sorting__quick_sort_helper_4_0,
		sorting__quick_sort_helper_4_0_i7);
MR_def_label(sorting__quick_sort_helper_4_0,7)
	MR_MAYBE_INIT_LOCAL_THREAD_ENGINE_BASE
	{
	MR_Word MR_tempr1;
	MR_tag_alloc_heap(MR_tempr1, 1, (MR_Integer) 2);
	MR_tfield(1, MR_tempr1, 0) = MR_sv(1);
	MR_tfield(1, MR_tempr1, 1) = MR_r2;
	MR_r2 = MR_tempr1;
	MR_decr_sp_and_return(2);
	}
#ifdef MR_maybe_local_thread_engine_base
	#undef MR_maybe_local_thread_engine_base
	#define MR_maybe_local_thread_engine_base MR_thread_engine_base
#endif
MR_END_MODULE

static void mercury__sorting_maybe_bunch_0(void)
{
	sorting_module0();
	sorting_module1();
	sorting_module2();
	sorting_module3();
	sorting_module4();
	sorting_module5();
	sorting_module6();
}

/* suppress gcc -Wmissing-decls warnings */
void mercury__sorting__init(void);
void mercury__sorting__init_type_tables(void);
void mercury__sorting__init_debugger(void);
#ifdef MR_DEEP_PROFILING
void mercury__sorting__write_out_proc_statics(FILE *deep_fp, FILE *procrep_fp);
#endif
#ifdef MR_RECORD_TERM_SIZES
void mercury__sorting__init_complexity_procs(void);
#endif
#ifdef MR_THREADSCOPE
void mercury__sorting__init_threadscope_string_table(void);
#endif

void mercury__sorting__init(void)
{
	static MR_bool done = MR_FALSE;
	if (done) {
		return;
	}
	done = MR_TRUE;
	mercury__sorting_maybe_bunch_0();
	mercury__sorting__init_debugger();
}

void mercury__sorting__init_type_tables(void)
{
	static MR_bool done = MR_FALSE;
	if (done) {
		return;
	}
	done = MR_TRUE;
}


void mercury__sorting__init_debugger(void)
{
	static MR_bool done = MR_FALSE;
	if (done) {
		return;
	}
	done = MR_TRUE;
}

#ifdef MR_DEEP_PROFILING

void mercury__sorting__write_out_proc_statics(FILE *deep_fp, FILE *procrep_fp)
{
	MR_write_out_module_proc_reps_start(procrep_fp, &mercury_data__module_layout__sorting);
	MR_write_out_module_proc_reps_end(procrep_fp);
}

#endif

#ifdef MR_RECORD_TERM_SIZES

void mercury__sorting__init_complexity_procs(void)
{
}

#endif

#ifdef MR_THREADSCOPE

void mercury__sorting__init_threadscope_string_table(void)
{
}

#endif

/* ensure everything is compiled with the same grade */
static const void *const MR_grade = &MR_GRADE_VAR;
