

sorting_tests.optdate sorting_tests.trans_opt_date sorting_tests.err sorting_tests.c_date sorting_tests.s_date sorting_tests.pic_s_date sorting_tests.il_date sorting_tests.java_date : sorting_tests.m \
	builtin.int \
	int.int \
	io.int \
	list.int \
	private_builtin.int \
	solutions.int \
	array.int2 \
	assoc_list.int2 \
	bitmap.int2 \
	bool.int2 \
	char.int2 \
	construct.int2 \
	deconstruct.int2 \
	enum.int2 \
	map.int2 \
	maybe.int2 \
	ops.int2 \
	pair.int2 \
	pretty_printer.int2 \
	random.int2 \
	rtti_implementation.int2 \
	set.int2 \
	set_ordlist.int2 \
	stream.int2 \
	string.int2 \
	term.int2 \
	time.int2 \
	tree234.int2 \
	type_desc.int2 \
	univ.int2

sorting_tests.mh sorting_tests.mih : sorting_tests.c


ifeq ($(findstring il,$(GRADE)),il)
sorting_tests.module_dep : sorting_tests.il
else
 ifeq ($(findstring java,$(GRADE)),java)
sorting_tests.module_dep : jmercury/sorting_tests.java
 else
sorting_tests.module_dep : sorting_tests.c
 endif
endif


sorting_tests.date sorting_tests.date0 : sorting_tests.m \
	builtin.int3 \
	int.int3 \
	io.int3 \
	list.int3 \
	private_builtin.int3 \
	solutions.int3 \
	array.int3 \
	assoc_list.int3 \
	bitmap.int3 \
	bool.int3 \
	char.int3 \
	construct.int3 \
	deconstruct.int3 \
	enum.int3 \
	map.int3 \
	maybe.int3 \
	ops.int3 \
	pair.int3 \
	pretty_printer.int3 \
	random.int3 \
	rtti_implementation.int3 \
	set.int3 \
	set_ordlist.int3 \
	stream.int3 \
	string.int3 \
	term.int3 \
	time.int3 \
	tree234.int3 \
	type_desc.int3 \
	univ.int3

sorting_tests.date0 : sorting_tests.m \
	builtin.int3 \
	int.int3 \
	io.int3 \
	list.int3 \
	private_builtin.int3 \
	solutions.int3 \
	array.int3 \
	assoc_list.int3 \
	bitmap.int3 \
	bool.int3 \
	char.int3 \
	construct.int3 \
	deconstruct.int3 \
	enum.int3 \
	map.int3 \
	maybe.int3 \
	ops.int3 \
	pair.int3 \
	pretty_printer.int3 \
	random.int3 \
	rtti_implementation.int3 \
	set.int3 \
	set_ordlist.int3 \
	stream.int3 \
	string.int3 \
	term.int3 \
	time.int3 \
	tree234.int3 \
	type_desc.int3 \
	univ.int3



sorting_tests.$O :  \
	array.mh \
	array.mh \
	time.mh \
	time.mh \
	bitmap.mh \
	bitmap.mh \
	string.mh \
	time.mh \
	io.mh \
	io.mh



sorting_tests.pic_o :  \
	array.mh \
	array.mh \
	time.mh \
	time.mh \
	bitmap.mh \
	bitmap.mh \
	string.mh \
	time.mh \
	io.mh \
	io.mh


sorting_tests.int0 : sorting_tests.date0
	@:
sorting_tests.int : sorting_tests.date
	@:
sorting_tests.int2 : sorting_tests.date
	@:
sorting_tests.int3 : sorting_tests.date3
	@:
sorting_tests.opt : sorting_tests.optdate
	@:
sorting_tests.trans_opt : sorting_tests.trans_opt_date
	@:
