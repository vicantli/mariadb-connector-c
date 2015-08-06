/************************************************************************************
  Copyright (C) 2014 MariaDB Corporation Ab

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public
  License along with this library; if not see <http://www.gnu.org/licenses>
  or write to the Free Software Foundation, Inc.,
  51 Franklin St., Fifth Floor, Boston, MA 02110, USA

  Author: Georg Richter

 *************************************************************************************/
#ifndef _ma_schannel_h_
#define _ma_schannel_h_

#define SECURITY_WIN32
#include <my_global.h>
#include <my_sys.h>
#include <ma_common.h>
#include <ma_cio.h>
#include <errmsg.h>
#include <mysql/client_plugin.h>

typedef void VOID;

#include <wincrypt.h>
#define SECURITY_WIN32
#include <security.h>
#include <schnlsp.h>
#undef SECURITY_WIN32
#include <Windows.h>

#define SC_IO_BUFFER_SIZE 0x4000

CERT_CONTEXT *ma_schannel_create_cert_context(const char *pem_file);
SECURITY_STATUS ma_schannel_handshake_loop(MARIADB_CIO *cio, my_bool InitialRead, SecBuffer *pExtraData);
my_bool ma_schannel_load_private_key(CERT_CONTEXT *ctx, char *key_file);
PCCRL_CONTEXT ma_schannel_create_crl_context(const char *pem_file);

#ifndef HAVE_SCHANNEL_DEFAULT
#define my_snprintf snprintf
#define my_vsnprintf vsnprintf
#undef SAFE_MUTEX
#endif
#include <my_pthread.h>

struct st_schannel {
  HCERTSTORE cert_store;
  CERT_CONTEXT *client_cert_ctx;
  CERT_CONTEXT *client_ca_ctx;
  CRL_CONTEXT *client_crl_ctx;
  CredHandle CredHdl;
  PUCHAR IoBuffer;
  DWORD IoBufferSize;
  PUCHAR DecryptBuffer;
  DWORD DecryptBufferSize;
  DWORD DecryptBufferLength;
  CtxtHandle ctxt;
};

typedef struct st_schannel SC_CTX;

#endif /* _ma_schannel_h_ */