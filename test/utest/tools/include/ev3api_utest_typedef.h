#pragma once
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * typedef for unit test
 * Copied from tool_stddef.h
 */
typedef signed char			int8_t;		/* 符号付き8ビット整数 */
typedef unsigned char		uint8_t;	/* 符号無し8ビット整数 */
typedef signed short		int16_t;	/* 符号付き16ビット整数 */
typedef unsigned short		uint16_t;	/* 符号無し16ビット整数 */
typedef signed int			int32_t;	/* 符号付き32ビット整数 */
typedef unsigned int		uint32_t;	/* 符号無し32ビット整数 */
typedef signed long long	int64_t;	/* 符号付き64ビット整数 */
typedef unsigned long long	uint64_t;	/* 符号無し64ビット整数 */
typedef int8_t				int_least8_t;	/* 8ビット以上の符号付き整数 */
typedef uint8_t				uint_least8_t;	/* 8ビット以上の符号無し整数 */
typedef long				intptr_t;	/* ポインタを格納できる符号付き整数 */
typedef unsigned long		uintptr_t;	/* ポインタを格納できる符号無し整数 */
typedef signed int			ID;
typedef signed int			ER;
typedef signed int			ER_ID;
typedef signed int			ER_UINT;
typedef signed int			bool_t;
typedef signed int			ISR;

#define E_OK		0
#define E_ID		1
#define E_PAR		2

#define true		(1)
#define false	(0)

typedef enum {
    EV3_PORT_A = 0,  	//!< \~English Port A				 \~Japanese ポートA
    EV3_PORT_B = 1,		//!< \~English Port B 				 \~Japanese ポートB
    EV3_PORT_C = 2,		//!< \~English Port C 				 \~Japanese ポートC
    EV3_PORT_D = 3, 	//!< \~English Port D 			     \~Japanese ポートD
    TNUM_MOTOR_PORT = 4 //!< \~English Number of motor ports \~Japanese モータポートの数
} motor_port_t;

typedef enum {
    NONE_MOTOR = 0,	   //!< \~English Not connected         \~Japanese モータ未接続
    MEDIUM_MOTOR,	   //!< \~English Medium servo motor    \~Japanese サーボモータM
    LARGE_MOTOR,	   //!< \~English Large servo motor     \~Japanese サーボモータL
    UNREGULATED_MOTOR, //!< \~English Unregulated motor     \~Japanese 未調整モータ
    TNUM_MOTOR_TYPE    //!< \~English Number of motor types \~Japanese モータタイプの数
} motor_type_t;

#ifdef __cplusplus
}
#endif

