/***************************************************************
 *
 * Copyright (C) 1990-2007, Condor Team, Computer Sciences Department,
 * University of Wisconsin-Madison, WI.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License.  You may
 * obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************/

#ifndef CONDOR_SOCKFUNC_H
#define CONDOR_SOCKFUNC_H

#include "condor_ipaddr.h"

int condor_connect(int sockfd, const ipaddr& addr);
int condor_accept(int sockfd, ipaddr& addr);
int condor_bind(int sockfd, const ipaddr& addr);
int condor_getsockname(int sockfd, ipaddr& addr);
int condor_getpeername(int sockfd, ipaddr& addr);

// if the sockfd has any address, it replaces with local ip address
int condor_getsockname_ex(int sockfd, ipaddr& addr);

int condor_getnameinfo (const ipaddr& addr,
				char * __host, socklen_t __hostlen, 
				char * __serv, socklen_t __servlen,
				unsigned int __flags);


int condor_getaddrinfo(const char *node,
                const char *service,
                const addrinfo *hints,
                addrinfo **res);

int condor_sendto(int sockfd, const void* buf, size_t len, int flags,
				  const ipaddr& addr);
int condor_recvfrom(int sockfd, void* buf, size_t buf_size, int flags,
		ipaddr& addr);

// create IPv6 socket if the build is configured to ipv6
// else create IPv4 socket
int condor_socket(int socket_type, int protocol);

// Reer the syntax of IP address
// from http://www.opengroup.org/onlinepubs/000095399/functions/inet_ntop.html

// it converts given text string to ipaddr.
// it automatically detects whether given text is ipv4 or ipv6.
// returns 0 if it is not ip address at all
// returns 1 if succeeded
int condor_inet_pton(const char* src, ipaddr& dest);

hostent* condor_gethostbyaddr_ipv6(const ipaddr& addr);
int condor_getsockaddr(int fd, ipaddr& addr);
// moved to my_hostname.h --> ipv6_hostname.h
//ipaddr ipv6_my_ip_addr();
int ipv6_is_ipaddr(const char* host, ipaddr& addr);
const char* ipv6_addr_to_hostname(const ipaddr& addr, char* buf, int len);

#endif // CONDOR_SOCKFUNC_H
