/*
 * eth_test.c
 *
 *  Created on: Jan 1, 2026
 *      Author: user
 */
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32f7xx.h"
#include "cmsis_os.h"
#include "console.h"

#include "eth.h"

extern uint8_t eth_send_data[5000];

static const ETH_OPEN eth_open_par = {
	COM_MODE_FULL_DUPLEX,
};

// オープン
void eth_test_open(void)
{
	osStatus ercd;
	
	// 送信
	ercd = eth_open(&eth_open_par);
	console_printf("eth_open:ercd = %d\n", ercd);
	
}

// 送信
void eth_test_send(void)
{
	osStatus ercd;
	
	// 送信
	ercd = eth_send(eth_send_data, sizeof(eth_send_data));
	console_printf("eth_send:ercd = %d\n", ercd);
	
}

// コマンド
static void eth_test_cmd(int argc, char *argv[])
{
	uint8_t idx;
	
	// 引数チェック
	if (argc < 2) {
		console_printf("eth_cmd <idx>\n");
		console_printf("eth_cmd 0 : eth_open\n");
		console_printf("eth_cmd 1 : eth_send\n");
		return;
	}
	
	// 値設定
	idx = atoi(argv[1]);
	
	if (idx == 0) {
		eth_test_open();
	} else if (idx == 1) {
		eth_test_send();
	} else {
		
	}
}

// コマンド設定関数
void eth_test_set_cmd(void)
{
	COMMAND_INFO cmd;
	
	// コマンドの設定
	cmd.input = "eth_cmd";
	cmd.func = eth_test_cmd;
	console_set_command(&cmd);
}

