/* 
 * Copyright (c) 1995, The University of Utah and
 * the Computer Systems Laboratory at the University of Utah (CSL).
 * All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software is hereby
 * granted provided that (1) source code retains these copyright, permission,
 * and disclaimer notices, and (2) redistributions including binaries
 * reproduce the notices in supporting documentation, and (3) all advertising
 * materials mentioning features or use of this software display the following
 * acknowledgement: ``This product includes software developed by the
 * Computer Systems Laboratory at the University of Utah.''
 *
 * THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
 * IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSL DISCLAIM ANY LIABILITY OF
 * ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * CSL requests users of this software to return to csl-dist@cs.utah.edu any
 * improvements that they make and grant CSL redistribution rights.
 *
 * 	Utah $Hdr: Nbsd_server.c 1.1 95/08/21$
 */

/*
 * XXX temporary XXX
 *
 * This file was actually generated by flick with SSTUBTRACE stuff added.
 */
#ifdef USENRPC

#define SSTUBTRACE
#ifdef SSTUBTRACE

static int verbose = 1;
static int callcount = 0;
#define CONDITION	(0)

#define Printf	if (CONDITION) printf
#endif

#include <mach/machine/flick_mach4_sstub.h>

#ifdef SSTUBTRACE
#undef mom_mach4_return
#define mom_mach4_return(rv)	{ retfoo = (rv); goto doreturn; }
#endif

/*static*/ int dispatcher(int _req_port, int _msg_id, int _seqno, int _moreacts)
{
  char *_recvbuffer = (char *) _bufsend;
  int _recviter = 0;
  char _sendbuffer[16384];
  int _senditer = 0;
{
  mom_signed32_t _t0_discrim;

#ifdef SSTUBTRACE
  int retfoo = 0;
  Printf("disp(x%x, x%x, x%x, x%x):\n", _req_port, _msg_id, _seqno, _moreacts);
  Printf("  p0=x%x, p1=%d, p2=x%x, p3=x%x", _param0, _param1, _param2, _param3);
  if (_portsnd)
    Printf(", prt=x%x, prtt=x%x", _portsnd, _porttype);
  if (_bufscnt)
    Printf(", memp=x%x, memc=x%x", _bufsend, _bufscnt);
  Printf("\n");
  if (verbose) {
    Printf("  p4=x%x, p5=x%x, p6=x%x, p7=x%x", _param4, _param5, _param6, _param7);
    if (_bufscnt > 0)
      Printf(", mem=x%x", ((int *)_bufsend)[0]);
    if (_bufscnt > 4)
      Printf("/x%x", ((int *)_bufsend)[1]);
    if (_bufscnt > 8)
      Printf("/x%x", ((int *)_bufsend)[2]);
    if (_bufscnt > 12)
      Printf("/x%x", ((int *)_bufsend)[3]);
    Printf("\n");
  }
#endif

  _t0_discrim = _param0;
  switch (_t0_discrim)
    {
      mom_signed32_t _t1_discrim;

    case 5065031:
      _t1_discrim = _param1;
      switch (_t1_discrim)
        {
        case 101000:
          {
            signed int arg_addr;
            signed int arg_size;
            signed int arg_count;
            signed int env_count;
            unsigned char *fname;
            signed int fnameCnt;
            unsigned int _return;

            arg_addr = _param2;
            arg_size = _param3;
            arg_count = _param4;
            env_count = _param5;
            fnameCnt = _param6;
            flick_mach4_decode_one_block(fname,fnameCnt * sizeof(unsigned char ));
            _return = bsd_execve(_req_port,_seqno,arg_addr,arg_size,arg_count,env_count,fname,fnameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101100;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101001:
          {
            signed int *arg_addr;
            signed int *arg_size;
            signed int *arg_count;
            signed int *env_count;
            mom_ref_t *image_port;
            unsigned char *emul_name;
            signed int *emul_nameCnt;
            unsigned char *fname;
            signed int *fnameCnt;
            unsigned char *cfname;
            signed int *cfnameCnt;
            unsigned char *cfarg;
            signed int *cfargCnt;
            unsigned int _return;
            signed int _t2_pstore;
            signed int _t3_pstore;
            signed int _t4_pstore;
            signed int _t5_pstore;
            mom_ref_t _t6_pstore;
            signed int _t7_pstore;

            arg_addr = &_t2_pstore;
            arg_size = &_t3_pstore;
            arg_count = &_t4_pstore;
            env_count = &_t5_pstore;
            image_port = &_t6_pstore;
            emul_nameCnt = &_t7_pstore;
            *emul_nameCnt = 1024;
            flick_mach4_encode_block(emul_name,1024 * sizeof(unsigned char ));
            flick_mach4_encode_int(fnameCnt);
            *fnameCnt = 1024;
            flick_mach4_encode_block(fname,1024 * sizeof(unsigned char ));
            flick_mach4_encode_int(cfnameCnt);
            *cfnameCnt = 1024;
            flick_mach4_encode_block(cfname,1024 * sizeof(unsigned char ));
            flick_mach4_encode_int(cfargCnt);
            *cfargCnt = 1024;
            flick_mach4_encode_block(cfarg,1024 * sizeof(unsigned char ));
            _return = bsd_after_exec(_req_port,_seqno,arg_addr,arg_size,arg_count,env_count,image_port,emul_name,emul_nameCnt,fname,fnameCnt,cfname,cfnameCnt,cfarg,cfargCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101101;
            _param2 = _return;
            _param3 = *arg_addr;
            _param4 = *arg_size;
            _param5 = *arg_count;
            _param6 = *env_count;
            _porttype = 17;
            _portsnd = (mom_ref_t )(*image_port);
            _param7 = *emul_nameCnt;
            _bufsend = (unsigned long) _sendbuffer;
            _bufscnt =  _senditer;
            mom_mach4_return(_return);
          }
          break;
        case 101002:
          {
            signed int *address;
            signed int size;
            signed int mask;
            signed int anywhere;
            mom_ref_t memory_object_representative;
            signed int offset;
            signed int copy;
            signed int cur_protection;
            signed int max_protection;
            signed int inheritance;
            unsigned int _return;
            signed int _t8_pstore;

            address = &_t8_pstore;
            *address = _param2;
            size = _param3;
            mask = _param4;
            anywhere = _param5;
            memory_object_representative = (mom_ref_t )_portsnd;
            offset = _param6;
            copy = _param7;
            flick_mach4_decode_int(cur_protection);
            flick_mach4_decode_int(max_protection);
            flick_mach4_decode_int(inheritance);
            _return = bsd_vm_map(_req_port,_seqno,address,size,mask,anywhere,memory_object_representative,offset,copy,cur_protection,max_protection,inheritance);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101102;
            _param2 = _return;
            _param3 = *address;
            mom_mach4_return(_return);
          }
          break;
        case 101003:
          {
            signed int fileno;
            mom_ref_t *port;
            unsigned int _return;
            mom_ref_t _t9_pstore;

            port = &_t9_pstore;
            fileno = _param2;
            _return = bsd_fd_to_file_port(_req_port,_seqno,fileno,port);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101103;
            _param2 = _return;
            _porttype = 17;
            _portsnd = (mom_ref_t )(*port);
            mom_mach4_return(_return);
          }
          break;
        case 101004:
          {
            signed int mode;
            signed int crtmode;
            unsigned char *fname;
            signed int fnameCnt;
            mom_ref_t *port;
            unsigned int _return;
            mom_ref_t _t10_pstore;

            port = &_t10_pstore;
            mode = _param2;
            crtmode = _param3;
            fnameCnt = _param4;
            flick_mach4_decode_one_block(fname,fnameCnt * sizeof(unsigned char ));
            _return = bsd_file_port_open(_req_port,_seqno,mode,crtmode,fname,fnameCnt,port);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101104;
            _param2 = _return;
            _porttype = 17;
            _portsnd = (mom_ref_t )(*port);
            mom_mach4_return(_return);
          }
          break;
        case 101006:
          {
            mom_ref_t sigport;
            unsigned int _return;

            sigport = (mom_ref_t )_portsnd;
            _return = bsd_signal_port_register(_req_port,_seqno,sigport);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101106;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101007:
          {
            signed int *new_state;
            signed int new_stateCnt;
            signed int *child_pid;
            unsigned int _return;
            signed int _t11_pstore;

            child_pid = &_t11_pstore;
            new_stateCnt = _param2;
            flick_mach4_decode_one_block(new_state,new_stateCnt * sizeof(signed int ));
            _return = bsd_fork(_req_port,_seqno,new_state,new_stateCnt,child_pid);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101107;
            _param2 = _return;
            _param3 = *child_pid;
            mom_mach4_return(_return);
          }
          break;
        case 101008:
          {
            signed int *new_state;
            signed int new_stateCnt;
            signed int *child_pid;
            unsigned int _return;
            signed int _t12_pstore;

            child_pid = &_t12_pstore;
            new_stateCnt = _param2;
            flick_mach4_decode_one_block(new_state,new_stateCnt * sizeof(signed int ));
            _return = bsd_vfork(_req_port,_seqno,new_state,new_stateCnt,child_pid);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101108;
            _param2 = _return;
            _param3 = *child_pid;
            mom_mach4_return(_return);
          }
          break;
        case 101009:
          {
            signed int *old_mask;
            signed int *old_onstack;
            signed int *sig;
            signed int *code;
            signed int *handler;
            signed int *new_sp;
            unsigned int _return;
            signed int _t13_pstore;
            signed int _t14_pstore;
            signed int _t15_pstore;
            signed int _t16_pstore;
            signed int _t17_pstore;

            old_mask = &_t13_pstore;
            old_onstack = &_t14_pstore;
            sig = &_t15_pstore;
            code = &_t16_pstore;
            handler = &_t17_pstore;
            flick_mach4_encode_int(new_sp);
            _return = bsd_take_signal(_req_port,_seqno,old_mask,old_onstack,sig,code,handler,new_sp);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101109;
            _param2 = _return;
            _param3 = *old_mask;
            _param4 = *old_onstack;
            _param5 = *sig;
            _param6 = *code;
            _param7 = *handler;
            _bufsend = (unsigned long) _sendbuffer;
            _bufscnt =  _senditer;
            mom_mach4_return(_return);
          }
          break;
        case 101010:
          {
            signed int old_on_stack;
            signed int old_sigmask;
            unsigned int _return;

            old_on_stack = _param2;
            old_sigmask = _param3;
            _return = bsd_sigreturn(_req_port,_seqno,old_on_stack,old_sigmask);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101110;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101011:
          {
            signed int which;
            signed int *rusage;
            unsigned int _return;
            mom_unsigned8_t _t18_array_length;

            flick_mach4_encode_one_block(rusage,18 * sizeof(signed int ));
            which = _param2;
            _return = bsd_getrusage(_req_port,_seqno,which,rusage);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101111;
            _param2 = _return;
            _t18_array_length = 18;
            _bufsend = (unsigned long) _sendbuffer;
            _bufscnt =  _senditer;
            mom_mach4_return(_return);
          }
          break;
        case 101012:
          {
            unsigned char *fname;
            signed int fnameCnt;
            unsigned int _return;

            fnameCnt = _param2;
            flick_mach4_decode_one_block(fname,fnameCnt * sizeof(unsigned char ));
            _return = bsd_chdir(_req_port,_seqno,fname,fnameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101112;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101013:
          {
            unsigned char *fname;
            signed int fnameCnt;
            unsigned int _return;

            fnameCnt = _param2;
            flick_mach4_decode_one_block(fname,fnameCnt * sizeof(unsigned char ));
            _return = bsd_chroot(_req_port,_seqno,fname,fnameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101113;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101014:
          {
            signed int mode;
            signed int crtmode;
            unsigned char *fname;
            signed int fnameCnt;
            signed int *fileno;
            unsigned int _return;
            signed int _t19_pstore;

            fileno = &_t19_pstore;
            mode = _param2;
            crtmode = _param3;
            fnameCnt = _param4;
            flick_mach4_decode_one_block(fname,fnameCnt * sizeof(unsigned char ));
            _return = bsd_open(_req_port,_seqno,mode,crtmode,fname,fnameCnt,fileno);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101114;
            _param2 = _return;
            _param3 = *fileno;
            mom_mach4_return(_return);
          }
          break;
        case 101015:
          {
            signed int fmode;
            signed int dev;
            unsigned char *fname;
            signed int fnameCnt;
            unsigned int _return;

            fmode = _param2;
            dev = _param3;
            fnameCnt = _param4;
            flick_mach4_decode_one_block(fname,fnameCnt * sizeof(unsigned char ));
            _return = bsd_mknod(_req_port,_seqno,fmode,dev,fname,fnameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101115;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101016:
          {
            unsigned char *target;
            signed int targetCnt;
            unsigned char *linkname;
            signed int linknameCnt;
            unsigned int _return;

            targetCnt = _param2;
            flick_mach4_decode_block(target,targetCnt * sizeof(unsigned char ));
            linknameCnt = _param3;
            flick_mach4_decode_block(linkname,linknameCnt * sizeof(unsigned char ));
            _return = bsd_link(_req_port,_seqno,target,targetCnt,linkname,linknameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101116;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101017:
          {
            unsigned char *target;
            signed int targetCnt;
            unsigned char *linkname;
            signed int linknameCnt;
            unsigned int _return;

            targetCnt = _param2;
            flick_mach4_decode_block(target,targetCnt * sizeof(unsigned char ));
            linknameCnt = _param3;
            flick_mach4_decode_block(linkname,linknameCnt * sizeof(unsigned char ));
            _return = bsd_symlink(_req_port,_seqno,target,targetCnt,linkname,linknameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101117;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101018:
          {
            unsigned char *fname;
            signed int fnameCnt;
            unsigned int _return;

            fnameCnt = _param2;
            flick_mach4_decode_one_block(fname,fnameCnt * sizeof(unsigned char ));
            _return = bsd_unlink(_req_port,_seqno,fname,fnameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101118;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101019:
          {
            signed int fmode;
            unsigned char *fname;
            signed int fnameCnt;
            unsigned int _return;

            fmode = _param2;
            fnameCnt = _param3;
            flick_mach4_decode_one_block(fname,fnameCnt * sizeof(unsigned char ));
            _return = bsd_access(_req_port,_seqno,fmode,fname,fnameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101119;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101020:
          {
            signed int count;
            unsigned char *name;
            signed int nameCnt;
            unsigned char *buf;
            signed int *bufCnt;
            unsigned int _return;
            signed int _t20_pstore;

            bufCnt = &_t20_pstore;
            *bufCnt = 8192;
            flick_mach4_encode_one_block(buf,8192 * sizeof(unsigned char ));
            count = _param2;
            nameCnt = _param3;
            flick_mach4_decode_one_block(name,nameCnt * sizeof(unsigned char ));
            _return = bsd_readlink(_req_port,_seqno,count,name,nameCnt,buf,bufCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101120;
            _param2 = _return;
            _param3 = *bufCnt;
            _bufsend = (unsigned long) _sendbuffer;
            _bufscnt =  _senditer;
            mom_mach4_return(_return);
          }
          break;
        case 101022:
          {
            unsigned char *from_name;
            signed int from_nameCnt;
            unsigned char *to_name;
            signed int to_nameCnt;
            unsigned int _return;

            from_nameCnt = _param2;
            flick_mach4_decode_block(from_name,from_nameCnt * sizeof(unsigned char ));
            to_nameCnt = _param3;
            flick_mach4_decode_block(to_name,to_nameCnt * sizeof(unsigned char ));
            _return = bsd_rename(_req_port,_seqno,from_name,from_nameCnt,to_name,to_nameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101122;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101023:
          {
            signed int dmode;
            unsigned char *name;
            signed int nameCnt;
            unsigned int _return;

            dmode = _param2;
            nameCnt = _param3;
            flick_mach4_decode_one_block(name,nameCnt * sizeof(unsigned char ));
            _return = bsd_mkdir(_req_port,_seqno,dmode,name,nameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101123;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101024:
          {
            unsigned char *name;
            signed int nameCnt;
            unsigned int _return;

            nameCnt = _param2;
            flick_mach4_decode_one_block(name,nameCnt * sizeof(unsigned char ));
            _return = bsd_rmdir(_req_port,_seqno,name,nameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101124;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101025:
          {
            signed int acct_on;
            unsigned char *fname;
            signed int fnameCnt;
            unsigned int _return;

            acct_on = _param2;
            fnameCnt = _param3;
            flick_mach4_decode_one_block(fname,fnameCnt * sizeof(unsigned char ));
            _return = bsd_acct(_req_port,_seqno,acct_on,fname,fnameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101125;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101026:
          {
            signed int fileno;
            unsigned char *data;
            signed int dataCnt;
            signed int *amount_written;
            unsigned int _return;
            signed int _t21_pstore;

            amount_written = &_t21_pstore;
            fileno = _param2;
            dataCnt = _param3;
            flick_mach4_decode_one_block(data,dataCnt * sizeof(unsigned char ));
            _return = bsd_write_short(_req_port,_seqno,fileno,data,dataCnt,amount_written);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101126;
            _param2 = _return;
            _param3 = *amount_written;
            mom_mach4_return(_return);
          }
          break;
        case 101028:
          {
            signed int fileno;
            signed int datalen;
            signed int *nread;
            unsigned char *data;
            signed int *dataCnt;
            unsigned int _return;
            signed int _t22_pstore;
            signed int _t23_pstore;

            nread = &_t22_pstore;
            dataCnt = &_t23_pstore;
            *dataCnt = 8192;
            flick_mach4_encode_one_block(data,8192 * sizeof(unsigned char ));
            fileno = _param2;
            datalen = _param3;
            _return = bsd_read_short(_req_port,_seqno,fileno,datalen,nread,data,dataCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101128;
            _param2 = _return;
            _param3 = *nread;
            _param4 = *dataCnt;
            _bufsend = (unsigned long) _sendbuffer;
            _bufscnt =  _senditer;
            mom_mach4_return(_return);
          }
          break;
        case 101036:
          {
            signed int gidsetsize;
            signed int *gidset;
            unsigned int _return;
            mom_unsigned8_t _t24_array_length;

            gidsetsize = _param2;
            _t24_array_length = 16;
            flick_mach4_decode_one_block(gidset,_t24_array_length * sizeof(signed int ));
            _return = bsd_setgroups(_req_port,_seqno,gidsetsize,gidset);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101136;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101037:
          {
            signed int which;
            signed int *lim;
            unsigned int _return;
            mom_unsigned8_t _t25_array_length;

            which = _param2;
            _t25_array_length = 4;
            flick_mach4_decode_one_block(lim,_t25_array_length * sizeof(signed int ));
            _return = bsd_setrlimit(_req_port,_seqno,which,lim);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101137;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101044:
          {
            signed int s;
            unsigned char *name;
            signed int nameCnt;
            unsigned int _return;

            s = _param2;
            nameCnt = _param3;
            flick_mach4_decode_one_block(name,nameCnt * sizeof(unsigned char ));
            _return = bsd_bind(_req_port,_seqno,s,name,nameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101144;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101046:
          {
            signed int s;
            unsigned char *name;
            signed int nameCnt;
            unsigned int _return;

            s = _param2;
            nameCnt = _param3;
            flick_mach4_decode_one_block(name,nameCnt * sizeof(unsigned char ));
            _return = bsd_connect(_req_port,_seqno,s,name,nameCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101146;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101047:
          {
            signed int s;
            signed int level;
            signed int name;
            unsigned char *val;
            signed int valCnt;
            unsigned int _return;

            s = _param2;
            level = _param3;
            name = _param4;
            valCnt = _param5;
            flick_mach4_decode_one_block(val,valCnt * sizeof(unsigned char ));
            _return = bsd_setsockopt(_req_port,_seqno,s,level,name,val,valCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101147;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101048:
          {
            signed int s;
            signed int level;
            signed int name;
            unsigned char *val;
            signed int *valCnt;
            unsigned int _return;
            signed int _t26_pstore;

            valCnt = &_t26_pstore;
            *valCnt = 128;
            flick_mach4_encode_one_block(val,128 * sizeof(unsigned char ));
            s = _param2;
            level = _param3;
            name = _param4;
            _return = bsd_getsockopt(_req_port,_seqno,s,level,name,val,valCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101148;
            _param2 = _return;
            _param3 = *valCnt;
            _bufsend = (unsigned long) _sendbuffer;
            _bufscnt =  _senditer;
            mom_mach4_return(_return);
          }
          break;
        case 101051:
          {
            unsigned int _return;

            _return = bsd_init_process(_req_port,_seqno);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101151;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101052:
          {
            signed int id;
            signed int index;
            signed int lel;
            signed int nel;
            unsigned char *addr;
            signed int addrCnt;
            signed int *nel_done;
            unsigned int _return;
            signed int _t27_pstore;

            nel_done = &_t27_pstore;
            id = _param2;
            index = _param3;
            lel = _param4;
            nel = _param5;
            addrCnt = _param6;
            flick_mach4_decode_one_block(addr,addrCnt * sizeof(unsigned char ));
            _return = bsd_table_set(_req_port,_seqno,id,index,lel,nel,addr,addrCnt,nel_done);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101152;
            _param2 = _return;
            _param3 = *nel_done;
            mom_mach4_return(_return);
          }
          break;
        case 101054:
          {
            unsigned char *err_message;
            signed int err_messageCnt;
            unsigned int _return;

            err_messageCnt = _param2;
            flick_mach4_decode_one_block(err_message,err_messageCnt * sizeof(unsigned char ));
            _return = bsd_emulator_error(_req_port,_seqno,err_message,err_messageCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101154;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101056:
          {
            signed int lock_offset;
            unsigned int _return;

            lock_offset = _param2;
            _return = bsd_share_wakeup(_req_port,_seqno,lock_offset);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101156;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101057:
          {
            signed int fileno;
            unsigned int _return;

            fileno = _param2;
            _return = bsd_maprw_request_it(_req_port,_seqno,fileno);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101157;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101058:
          {
            signed int fileno;
            unsigned int _return;

            fileno = _param2;
            _return = bsd_maprw_release_it(_req_port,_seqno,fileno);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101158;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101059:
          {
            signed int fileno;
            signed int offset;
            signed int size;
            unsigned int _return;

            fileno = _param2;
            offset = _param3;
            size = _param4;
            _return = bsd_maprw_remap(_req_port,_seqno,fileno,offset,size);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101159;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101061:
          {
            signed int *sample_flavor;
            unsigned int _return;
            signed int _t28_pstore;

            sample_flavor = &_t28_pstore;
            *sample_flavor = _param2;
            _return = bsd_mon_switch(_req_port,_seqno,sample_flavor);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101161;
            _param2 = _return;
            _param3 = *sample_flavor;
            mom_mach4_return(_return);
          }
          break;
        case 101063:
          {
            signed int fileno;
            signed int *vattr;
            unsigned int _return;
            mom_unsigned8_t _t29_array_length;

            flick_mach4_encode_one_block(vattr,24 * sizeof(signed int ));
            fileno = _param2;
            _return = bsd_getattr(_req_port,_seqno,fileno,vattr);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101163;
            _param2 = _return;
            _t29_array_length = 24;
            _bufsend = (unsigned long) _sendbuffer;
            _bufscnt =  _senditer;
            mom_mach4_return(_return);
          }
          break;
        case 101065:
          {
            signed int follow;
            unsigned char *path;
            signed int pathCnt;
            signed int *vattr;
            unsigned int _return;
            mom_unsigned8_t _t30_array_length;

            flick_mach4_encode_one_block(vattr,24 * sizeof(signed int ));
            follow = _param2;
            pathCnt = _param3;
            flick_mach4_decode_one_block(path,pathCnt * sizeof(unsigned char ));
            _return = bsd_path_getattr(_req_port,_seqno,follow,path,pathCnt,vattr);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101165;
            _param2 = _return;
            _t30_array_length = 24;
            _bufsend = (unsigned long) _sendbuffer;
            _bufscnt =  _senditer;
            mom_mach4_return(_return);
          }
          break;
        case 101068:
          {
            unsigned char *what_to_expand;
            signed int what_to_expandCnt;
            unsigned char *expansion;
            signed int expansionCnt;
            unsigned int _return;

            what_to_expandCnt = _param2;
            flick_mach4_decode_block(what_to_expand,what_to_expandCnt * sizeof(unsigned char ));
            expansionCnt = _param3;
            flick_mach4_decode_block(expansion,expansionCnt * sizeof(unsigned char ));
            _return = bsd_set_atexpansion(_req_port,_seqno,what_to_expand,what_to_expandCnt,expansion,expansionCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101168;
            _param2 = _return;
            mom_mach4_return(_return);
          }
          break;
        case 101069:
          {
            signed int fileno;
            signed int flags;
            unsigned char *data;
            signed int dataCnt;
            unsigned char *to;
            signed int toCnt;
            unsigned char *cmsg;
            signed int cmsgCnt;
            signed int *nsent;
            unsigned int _return;
            signed int _t31_pstore;

            nsent = &_t31_pstore;
            fileno = _param2;
            flags = _param3;
            dataCnt = _param4;
            flick_mach4_decode_block(data,dataCnt * sizeof(unsigned char ));
            toCnt = _param5;
            flick_mach4_decode_block(to,toCnt * sizeof(unsigned char ));
            cmsgCnt = _param6;
            flick_mach4_decode_block(cmsg,cmsgCnt * sizeof(unsigned char ));
            _return = bsd_sendmsg_short(_req_port,_seqno,fileno,flags,data,dataCnt,to,toCnt,cmsg,cmsgCnt,nsent);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101169;
            _param2 = _return;
            _param3 = *nsent;
            mom_mach4_return(_return);
          }
          break;
        case 101071:
          {
            signed int fileno;
            signed int flags;
            signed int *outflags;
            signed int fromlen;
            signed int *nreceived;
            unsigned char *from;
            signed int *fromCnt;
            signed int cmsglen;
            unsigned char *cmsg;
            signed int *cmsgCnt;
            signed int datalen;
            unsigned char *data;
            signed int *dataCnt;
            unsigned int _return;
            signed int _t32_pstore;
            signed int _t33_pstore;
            signed int _t34_pstore;
            signed int _t35_pstore;
            signed int _t36_pstore;

            outflags = &_t32_pstore;
            nreceived = &_t33_pstore;
            fromCnt = &_t34_pstore;
            *fromCnt = 128;
            flick_mach4_encode_block(from,128 * sizeof(unsigned char ));
            cmsgCnt = &_t35_pstore;
            *cmsgCnt = 128;
            flick_mach4_encode_block(cmsg,128 * sizeof(unsigned char ));
            dataCnt = &_t36_pstore;
            *dataCnt = 8192;
            flick_mach4_encode_block(data,8192 * sizeof(unsigned char ));
            fileno = _param2;
            flags = _param3;
            fromlen = _param4;
            cmsglen = _param5;
            datalen = _param6;
            _return = bsd_recvmsg_short(_req_port,_seqno,fileno,flags,outflags,fromlen,nreceived,from,fromCnt,cmsglen,cmsg,cmsgCnt,datalen,data,dataCnt);
            _portsnd = 0;
            _bufsend = 0;
            _param0 = 5065031;
            _param1 = 101171;
            _param2 = _return;
            _param3 = *outflags;
            _param4 = *nreceived;
            _param5 = *fromCnt;
            _bufsend = (unsigned long) _sendbuffer;
            _bufscnt =  _senditer;
            _param6 = *cmsgCnt;
            _param7 = *dataCnt;
            mom_mach4_return(_return);
          }
          break;
        }
      break;
    }

#ifdef SSTUBTRACE
doreturn:
  Printf("  p0=x%x, p1=%d, p2=x%x, p3=x%x", _param0, _param1, _param2, _param3);
  if (_portsnd)
    Printf(", prt=x%x, prtt=x%x", _portsnd, _porttype);
  if (_bufsend == 0)
    _bufscnt = 0;
  if (_bufscnt)
    Printf(", memp=x%x, memc=x%x", _bufsend, _bufscnt);
  Printf(", ret=x%x\n", retfoo);
  if (verbose) {
    Printf("  p4=x%x, p5=x%x, p6=x%x, p7=x%x", _param4, _param5, _param6, _param7);
    if (_bufscnt > 0)
      Printf(", mem=x%x", ((int *)_bufsend)[0]);
    if (_bufscnt > 4)
      Printf("/x%x", ((int *)_bufsend)[1]);
    if (_bufscnt > 8)
      Printf("/x%x", ((int *)_bufsend)[2]);
    if (_bufscnt > 12)
      Printf("/x%x", ((int *)_bufsend)[3]);
    Printf("\n");
  }
  callcount++;
  return (retfoo);
#endif

}
}
extern void asmdispatcher(void);
asm("
	 .align 4
	 .EXPORT asmdispatcher,ENTRY
asmdispatcher
	 .PROC
	 .CALLINFO FRAME=64,CALLS
	 .ENTRY
	 bl	dispatcher,%r2
	 ldo	64(%sp),%sp
	 ldil	L%0xC0000000,%r1
	 ble	0x10(%sr7,%r1)
	 nop
	 .EXIT
	 .PROCEND ");
struct flick_server the_server = { dispatcher, asmdispatcher, 8192 };
#endif
