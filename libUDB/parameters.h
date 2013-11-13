/* 
 * File:   parameter_macros.h
 * Author: Matt
 *
 * Created on 10 November 2013, 06:23
 */

#ifndef PARAMETER_MACROS_H
#define	PARAMETER_MACROS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../MatrixPilot/parameter_table.h"

#define PARAM_COUNT 0

///**
// * Parameter types.
// */
//typedef enum param_type_e {
//	/* globally-known parameter types */
//	PARAM_TYPE_INT32 = 0,
//	PARAM_TYPE_FLOAT,
//
//	/* structure parameters; size is encoded in the type value */
//	PARAM_TYPE_STRUCT = 100,
//	PARAM_TYPE_STRUCT_MAX = 16384 + PARAM_TYPE_STRUCT,
//
//	PARAM_TYPE_UNKNOWN = 0xffff
//} param_type_t;

/**
 * Parameter handle.
 *
 * Parameters are represented by parameter handles, which can
 * be obtained by looking up (or creating?) parameters.
 */
//typedef uintptr_t	param_t;

/**
 * Handle returned when a parameter cannot be found.
 */
#define PARAM_INVALID	((uintptr_t)0xffffffff)


/*
 * Macros creating static parameter definitions.
 *
 * Note that these structures are not known by name; they are
 * collected into a section that is iterated by the parameter
 * code.
 *
 * Note that these macros cannot be used in C++ code due to
 * their use of designated initializers.  They should probably
 * be refactored to avoid the use of a union for param_value_u.
 */

/** define an int32 parameter */
#define PARAM_DEFINE_INT(_name, _pvar, _min, _max, _readOnly)		\
	static const					\
	__attribute__((used, section("__param")))	\
	struct param_info_s __param__##_name = {	\
		#_name,					\
		(uint8_t*) _pvar,					\
		UDB_TYPE_INT,                           \
		.min.param_int32 = _min,                \
		.max.param_int32 = _max,           	\
                _readOnly                               \
	}

/** define an int32 parameter */
#define PARAM_DEFINE_Q14(_name, _pvar, _min, _max, _readOnly)		\
	static const					\
	__attribute__((used, section("__param")))	\
	struct param_info_s __param__##_name = {	\
		#_name,					\
		(uint8_t*) _pvar,					\
		UDB_TYPE_Q14,                     	\
		.min.param_float = _min,                \
		.max.param_float = _max,           	\
                _readOnly                               \
	}

    
/** define a float parameter */
#define PARAM_DEFINE_FLOAT(_name, _default)		\
	static const					\
	__attribute__((used, section("__param")))	\
	struct param_info_s __param__##_name = {	\
		#_name,					\
		PARAM_TYPE_FLOAT,			\
		.val.f = _default			\
	}

/** define a parameter that points to a structure */
#define PARAM_DEFINE_STRUCT(_name, _default)		\
	static const					\
	__attribute__((used, section("__param")))	\
	struct param_info_s __param__##_name = {	\
		#_name,					\
		PARAM_TYPE_STRUCT + sizeof(_default),	\
		.val.p = &_default;			\
	}

/** define a parameter that is the start of the list */
#define PARAM_DEFINE_START()                            \
	static const					\
	__attribute__((used, section("__pstart")))	\
	struct param_info_s __param__the_start = {    	\
		NULL,					\
		NULL,					\
	}

/** define a parameter that that is the end of the list */
#define PARAM_DEFINE_END()                              \
	static const					\
	__attribute__((used, section("__pend")))	\
	struct param_info_s __param__the_end = {    	\
		NULL,					\
		NULL,					\
	}



#define param_value_u param_union_t

/**
 * Static parameter definition structure.
 *
 * This is normally not used by user code; see the PARAM_DEFINE macros
 * instead.
 */
struct param_info_s {
	const char          *name;          // name of parameter
	uint8_t*            pvar;           // Reference to variable
	udb_internal_type_e type;           // Internal type of variable
	param_union_t       min;            // parameter minimum
	param_union_t       max;            // parameter maximum
        boolean             readOnly;       // Is read only
};



/**
 * Static parameter section definition structure.
 *
 * This is normally not used by user code; see the PARAM_DEFINE macros
 * instead.
 */
struct param_section_s {
	const char              *name;
        uint16_t                flags;
        PT_callbackFunc         ploadCallback;
};



/** define a parameter that is the start of the list */
#define PARAM_SECTION_START()                            \
	static const					\
	__attribute__((used, section("__sstart")))	\
	struct param_section_s __section__the_start = {    	\
		NULL,					\
		NULL,					\
		NULL,					\
	}

/** define a parameter that that is the end of the list */
#define PARAM_SECTION_END()                              \
	static const					\
	__attribute__((used, section("__send")))	\
	struct param_section_s __section__the_end = {    	\
		NULL,					\
		NULL,					\
		NULL,					\
	}


/** define a parameter that is the start of the list */
#define PARAM_SECTION(_name, _flags, _callback)         \
	static const					\
	__attribute__((used, section("__section")))	\
	struct param_section_s __section__the_start = { \
		#_name,					\
		_flags,					\
		_callback,				\
	}



#ifdef	__cplusplus
}
#endif

#endif	/* PARAMETER_MACROS_H */
