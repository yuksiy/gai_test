/*
==============================================================================
  機能
    IPv6 宛先アドレス選択のテストツール
  構文
    usage 参照

  Copyright (c) 2011-2017 Yukio Shiiya

  This software is released under the MIT License.
  https://opensource.org/licenses/MIT
==============================================================================
*/

/*
######################################################################
# 基本設定
######################################################################
*/
#if defined(__MINGW32__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
/* #include <iphlpapi.h> */
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

#include <stdio.h>
#include <string.h>	/* memset */
#include <stdlib.h>	/* EXIT_FAILURE,EXIT_SUCCESS,abort,exit */

/*
######################################################################
# 変数宣言 (グローバル)
######################################################################
*/
#if defined(__MINGW32__)
WORD	version_requested = MAKEWORD(2,2);
WSADATA	wsadata;
#endif

int	iresult;

/*
######################################################################
# 関数定義
######################################################################
*/
void pre_process(void);
void post_process(void);
void usage(void);

void pre_process(void)
{
#if defined(__MINGW32__)
	/* DLL の使用開始 */
	iresult = WSAStartup(version_requested, &wsadata);
	if (iresult != 0) {
		fprintf(stderr, "-E WSAStartup failed with return code: %d\n", iresult);
		exit(EXIT_FAILURE);
	}
	if (wsadata.wVersion != version_requested) {
		fprintf(stderr, "-E Loaded Winsock %u.%u but requested %u.%u\n",
			LOBYTE(wsadata.wVersion), HIBYTE(wsadata.wVersion),
			LOBYTE(version_requested), HIBYTE(version_requested)
		);
		post_process();exit(EXIT_FAILURE);
	}
#endif
}

void post_process(void)
{
#if defined(__MINGW32__)
	/* DLL の使用終了 */
	WSACleanup();
#endif
}

void usage(void)
{
	fputs("\
Usage:\n\
    gai_test HostName\n\
", stderr);
	exit(EXIT_FAILURE);
}

/*
######################################################################
# メインルーチン
######################################################################
*/
int main(int argc, char *argv[])
{
	/* 変数宣言 */
	const char	*szHostName;
	struct addrinfo	hints;
	struct addrinfo	*result = NULL;

	void	*addr;
	char	szStringBuf[INET6_ADDRSTRLEN];
#if defined(__MINGW32__)
	DWORD	dwStringBufLength;
#endif

	struct addrinfo	*addrinfo = NULL;

	/* 必須引数の処理 */
	/* 第1引数の処理 */
	if (argc < 2) {
		fprintf(stderr, "-E Missing HostName argument\n");
		usage();
	} else {
		szHostName = argv[1];
	}

	/* 作業開始前処理 */
	pre_process();

	/* アドレス情報の取得 */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	iresult = getaddrinfo(szHostName, NULL, &hints, &result);
	if (iresult != 0) {
		fprintf(stderr, "-E getaddrinfo failed: %s\n", gai_strerror(iresult));
		post_process();exit(EXIT_FAILURE);
	}

	/* 変換後アドレスの表示 */
	for (addrinfo = result; addrinfo != NULL; addrinfo = addrinfo->ai_next) {
#if defined(__MINGW32__)
		dwStringBufLength = sizeof(szStringBuf);
		WSAAddressToString(addrinfo->ai_addr, (DWORD)addrinfo->ai_addrlen, NULL, szStringBuf, &dwStringBufLength);
#else
		/* IPv4 の場合 */
		if (addrinfo->ai_family == AF_INET) {
			struct sockaddr_in *sockaddr = (struct sockaddr_in *) addrinfo->ai_addr;
			addr = &(sockaddr->sin_addr);
		/* IPv6 の場合 */
		} else if (addrinfo->ai_family == AF_INET6) {
			struct sockaddr_in6 *sockaddr = (struct sockaddr_in6 *) addrinfo->ai_addr;
			addr = &(sockaddr->sin6_addr);
		}
		inet_ntop(addrinfo->ai_family, addr, szStringBuf, sizeof(szStringBuf));
#endif
		printf("%s\n", szStringBuf);
	}

	/* アドレス情報の開放 */
	freeaddrinfo(result);

	/* 作業終了後処理 */
	post_process();exit(EXIT_SUCCESS);
}

