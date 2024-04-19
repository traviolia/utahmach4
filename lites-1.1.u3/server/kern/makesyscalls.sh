#! /bin/sh -
# 
# Mach Operating System
# Copyright (c) 1992 Carnegie Mellon University
# Copyright (c) 1994 Johannes Helander
# All Rights Reserved.
# 
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
# 
# CARNEGIE MELLON AND JOHANNES HELANDER ALLOW FREE USE OF THIS
# SOFTWARE IN ITS "AS IS" CONDITION.  CARNEGIE MELLON AND JOHANNES
# HELANDER DISCLAIM ANY LIABILITY OF ANY KIND FOR ANY DAMAGES
# WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
#
# HISTORY
# $Log: makesyscalls.sh,v $
# Revision 1.1.1.1  1995/03/02  21:49:45  mike
# Initial Lites release from hut.fi
#
# 
#	File: 	server/kern/makesyscalls.sh
#	Authors:
#	Randall Dean, Carnegie Mellon University, 1992.
#	Johannes Helander, Helsinki University of Technology, 1994.
#
# HISTORY
# $Log: makesyscalls.sh,v $
# Revision 1.1.1.1  1995/03/02  21:49:45  mike
# Initial Lites release from hut.fi
#
#

set -e

# name of compat option:
compat=COMPAT_43

# output files:
sysnames="syscalls.c"
syshdr="../sys/syscall.h"
syssw="init_sysent.c"
syse="../emul_sysent.c"
sysprot="../sys/sysproto.h"
eprot="../sys/eproto.h"
syslib="../libsys"
jacketlib="../libjacket"

# tmp files:
sysdcl="sysent.dcl"
syscompat="sysent.compat"
sysent="sysent.switch"
emldcl="emlent.dcl"
emlent="emlent.switch"

trap "rm $sysdcl $syscompat $sysent $emldcl $emlent" 0

case $# in
    0)	echo "Usage: $0 input-file" 1>&2
	exit 1
	;;
esac
echo
awk < $1 "
	BEGIN {
		sysdcl = \"$sysdcl\"
		syscompat = \"$syscompat\"
		sysent = \"$sysent\"
		sysnames = \"$sysnames\"
		syshdr = \"$syshdr\"
		sysproto = \"$sysprot\"
		eproto = \"$eprot\"
		syslibdir = \"$syslib\"
		jacketdir = \"$jacketlib\"
		compat = \"$compat\"
		emldcl = \"$emldcl\"
		emlent = \"$emlent\"
		infile = \"$1\"
		"'

		printf "/*\n * System call switch table.\n *\n" > sysdcl
		printf " * DO NOT EDIT-- this file is automatically generated.\n" > sysdcl

		printf "\n#if %s\n", compat > syscompat
		printf "#define compat(n, name) n, __CONCAT(o,name)\n\n" > syscompat

		printf "/*\n * System call names.\n *\n" > sysnames
		printf " * DO NOT EDIT-- this file is automatically generated.\n" > sysnames

		printf "/*\n * System call numbers.\n *\n" > syshdr
		printf " * DO NOT EDIT-- this file is automatically generated.\n" > syshdr

		printf "/*\n * System call prototypes.\n *\n" > sysproto
		printf " * DO NOT EDIT-- this file is automatically generated.\n" > sysproto

		printf "/*\n * Re-entrant system call prototypes.\n *\n" > eproto
		printf " * DO NOT EDIT-- this file is automatically generated.\n" > eproto

		printf "/*\n * System call switch table.\n *\n" > emldcl
		printf " * DO NOT EDIT-- this file is automatically generated.\n" > emldcl

	}
	NR == 1 {
		printf " * created from%s\n */\n\n", infile > sysdcl
		printf "#include <ktrace.h>\n" > sysdcl
		printf "#include <compat_43.h>\n" > sysdcl
		printf "#include <sys/param.h>\n" > sysdcl
		printf "#include <sys/systm.h>\n\n" > sysdcl
		printf "int\tnosys();\n\n" > sysdcl

		printf "struct sysent sysent[] = {\n" > sysent

		printf " * created from%s\n */\n\n", infile > sysnames
		printf "char *syscallnames[] = {\n" > sysnames

		printf " * created from%s\n */\n\n", infile > syshdr
		printf " * created from%s\n */\n\n", infile > sysproto
		printf " * created from%s\n */\n\n", infile > eproto

		printf " * created from%s\n */\n\n", infile > emldcl
		printf "#include <syscall_table.h>\n" > emldcl
		printf "#define syss(routine, nargs)    { nargs, routine }\n" >emldcl
		printf "#define sysg(routine, nargs)    { E_GENERIC, emul_generic }\n" > emldcl
		printf "#define sysr(routine)           { E_CHANGE_REGS, routine }\n" > emldcl
		printf "#define syse(routine)           { E_GENERIC, routine }\n" > emldcl
		printf "int emul_generic();\n" > emldcl
		printf "int e_htg_syscall();\n" > emldcl
		printf "int bsd_pid_by_task();\n" > emldcl
		printf "int bsd_task_by_pid();\n" > emldcl
		printf "int bsd_init_process();\n" > emldcl
		printf "#define e_setgroups	bsd_setgroups\n" > emldcl
		printf "#define e_sethostname	bsd_sethostname\n" > emldcl
		printf "#define e_connect	bsd_connect\n" > emldcl
		printf "#define e_bind		bsd_bind\n" > emldcl
		printf "#define e_adjtime	bsd_adjtime\n" > emldcl
		printf "#define e_setrlimit	bsd_setrlimit\n" > emldcl

		printf "struct sysent sysent[] = {\n" > emlent

		next
	}
	NF == 0 || $1 ~ /^;/ {
		next
	}
	$1 ~ /^#[ 	]*if/ {
		print > sysent
		print > sysdcl
		print > syscompat
		print > sysnames
		print > sysproto
		print > eproto
		print > emldcl
		print > emlent
		savesyscall = syscall
		next
	}
	$1 ~ /^#[ 	]*else/ {
		print > sysent
		print > sysdcl
		print > syscompat
		print > sysnames
		print > sysproto
		print > eproto
		print > emldcl
		print > emlent
		syscall = savesyscall
		next
	}
	$1 ~ /^#/ {
		print > sysent
		print > sysdcl
		print > syscompat
		print > sysnames
		print > sysproto
		print > eproto
		print > emldcl
		print > emlent
		next
	}
	syscall != $1 {
		printf "%s: line %d: syscall number out of sync at %d\n", \
		   infile, NR, syscall
		printf "line is:\n"
		print
		exit 1
	}
	{	comment = $5
		for (i = 6; i <= NF; i++)
			comment = comment " " $i
		if (NF < 6)
			$6 = $5
	}
	$3 == "SYSG" {
		printf("\tsysg(e_%s, %d),\t\t\t\t/* %d */\n",$5,$4,syscall) > emlent
	}
	$3 == "SYSR" {
		printf("\tsysr(e_%s),\t\t\t/* %d */\n",$5,syscall) > emlent
		printf("int e_%s();\n",$5) > emldcl
	}
	$3 == "SYSE" {
		printf("\tsyse(e_%s),\t\t\t/* %d */\n",$5,syscall) > emlent
		printf("int e_%s();\n",$5) > emldcl
	}
	$3 == "SYSS" {
		printf("\tsyss(e_%s, %d),\t\t/* %d */\n",$5,$4,syscall) > emlent
		printf("int e_%s();\n",$5) > emldcl
	}
	$2 == "STD" || $2 == "EMUL" {
		sname= $6
		iname= $5
		if (NF < 7 || $7 == "?") {
			returntype="int"
		} else {
			returntype=$7
		}
		if (NF < 8 || $8 == "?") {
			retname="retval"
		} else {
			retname=$8
		}
		if ($2 == "STD") {
			printf("int\t%s();\n", iname) > sysdcl
			printf("\t%d, %s,\t\t\t/* %d = %s */\n", \
			    $3, iname, syscall, sname) > sysent
		} else {
			printf("\t0, nosys,\t\t\t/* %d = emulated %s */\n", \
			    syscall, sname) > sysent
		}
		printf("\t\"%s\",\t\t\t/* %d = %s */\n", \
		    sname, syscall, sname) > sysnames
		printf("#define\tSYS_%s\t%d\n", \
		    sname, syscall) > syshdr

		elib="libe.c"
		if (returntype == "junk") {
			printf("extern int %s", sname) > sysproto
		} else {
			printf("extern %s %s", returntype, sname) > sysproto
		}
		if (returntype == "noreturn") {
			libfile= "/dev/null"
			jacket= "/dev/null"
			printf("extern noreturn %s", sname) > eproto
			printf("noreturn %s", sname) > elib
			printf("noreturn dev_null_%s", sname) > jacket
		} else {
			libfile=syslibdir "/" sname ".c"
			jacket= jacketdir "/e_" iname ".c"
			printf("extern errno_t e_%s", iname) > eproto
			printf("errno_t e_%s", iname) > elib
			printf("/* \n * %s\n", jacket) > jacket
			printf(" * DO NOT EDIT-- this file is automatically generated.\n") > jacket
			printf(" * created from %s\n */\n", infile) > jacket
			printf("\n#include <sys/libjacket.h>\n\n") > jacket
			printf("errno_t e_%s", iname) > jacket
		}
		printf("/* \n * %s\n", libfile) > libfile
		printf(" * DO NOT EDIT-- this file is automatically generated.\n") > libfile
		printf(" * created from %s\n */\n", infile) > libfile
		printf("\n#include <sys/libsys.h>\n\n") > libfile
		if (returntype == "junk") {
			printf("int %s", sname) > libfile
		} else {
			printf("%s %s", returntype, sname) > libfile
		}
		avarcomma=""
		avar=""
		nargs = $4
		if (nargs == 0) {
			# empty arglist
			printf("(void);\n") > sysproto
			if (returntype == "noreturn") {
				printf("(void);\n") > eproto
				printf("()\n{\n") > elib
				printf("()\n{\n") > jacket
			} else if (returntype == "junk") {
				printf("(void);\n") > eproto
				printf("()\n{\n") > elib
				printf("()\n{\n") > jacket
			} else {
				printf("(%s *%s);\n", returntype, retname) > eproto
				printf("(%s *%s)\n{\n", returntype, retname) > elib
				printf("(%s *%s)\n{\n", returntype, retname) > jacket
			}
			printf("\terrno_t err;\n\tkern_return_t kr;\n\tint intr, rv[2];\n\n\tstruct {\n\t\tint dummy;\n\t} a;\n") > elib
			printf("()\n") > libfile
		} else {
			# get arglist including types into ARGS
			$1="";$2="";$3="";$4="";$5="";$6="";$7="";$8=""
			args=substr($0,9)
			# function header
			printf("(%s);\n", args) > sysproto
			if (returntype == "noreturn") {
				printf("(%s);\n", args) > eproto
				printf("(%s)\n{\n", args) > elib
				printf("(%s)\n{\n", args) > jacket
			} else if (returntype == "junk") {
				printf("(%s);\n", args) > eproto
				printf("(%s)\n{\n", args) > elib
				printf("(%s)\n{\n", args) > jacket
			} else {
				printf("(%s, %s *%s);\n",
					 args, returntype, retname) > eproto
				printf("(%s, %s *%s)\n{\n", args, returntype, retname) > elib
				printf("(%s, %s *%s)\n{\n", args, returntype, retname) > jacket
			}
			printf("(%s)\n", args) > libfile
			printf("\terrno_t err;\n\tkern_return_t kr;\n\tint intr, rv[2];\n\n\tstruct {\n") > elib
			tmp=args
			gsub(", ", ";\n\t\t", tmp)
			printf("\t\t%s;\n\t} a;\n", tmp) > elib
			# get arglist without types to AVAR
			n=split(args, avararray, ",")
			# (and do some sanity checking on the way)
			if (n != nargs) {
				printf("%s: line %d: argument count does not match for %s (%d != %d) %s\n", infile, NR, sname, n, nargs, tmp)
			exit 1
			}
			firstx="yes"
			for (x = 1; x <= n; x++) {
				gsub(".+ ", "", avararray[x])
				gsub("[[*][0-9]*[]]*", "", avararray[x])
				if (firstx == "yes") {
					avar = avararray[x]
				} else {
					avar = avar ", " avararray[x]
				}
				printf("\ta.%s = %s;\n", avararray[x], avararray[x]) > elib
				firstx="no"
			}
			# done with AVAR, continue outputting stuff
			avarcomma= avar ", "
		}
		printf("\n\tkr = emul_generic(our_bsd_server_port, &intr, SYS_%s, &a, &rv);\n", sname) > elib
		printf("\terr = kr ? e_mach_error_to_errno(kr) : 0;\n") > elib
		printf("\terrno_t err, tmp;\n\n\terrno_jacket_lock();\n") > jacket
		printf("\ttmp = errno;\n\terrno = 0;\n\t") > jacket
		if (returntype == "junk") {
			printf("{\n\terrno_t err;\n\n\terr = e_%s(%s);\n",
				iname, avar) > libfile
			printf("\tif (err != 0) {\n\t\terrno = err;\n\t\treturn -1;\n\t}\n") > libfile
			printf("\treturn 0;\n}\n\n") > libfile

		} else {
			printf("\tif (err == 0)\n\t\t*%s = rv[0];\n", retname) > elib
			printf("{\n\t%s %s = 0;\n\terrno_t err;\n\n\terr = e_%s(%s&%s);\n",
				returntype, retname, iname, avarcomma, retname) > libfile
			printf("\tif (err != 0) {\n\t\t%s = -1;\n",
				 retname) > libfile
			printf("\t\terrno = err;\n\t}\n\treturn %s;\n}\n\n",
				retname) > libfile
			printf("*%s = ", retname) > jacket
		}
		printf("\treturn err;\n}\n\n") > elib
		printf("%s(%s);\n", sname, avar) > jacket
		printf("\terr = errno;\n\terrno = tmp;\n") > jacket
		printf("\terrno_jacket_unlock();\n\n\treturn err;\n}\n\n") > jacket
		if (jacket != "/dev/null")
			close(jacket)
		if (libfile != "/dev/null")
			close(libfile)

		syscall++
		next
	}
	$2 == "COMPAT" {
		printf("int\to%s();\n", $5) > syscompat
		printf("\tcompat(%d,%s),\t\t/* %d = old %s */\n", \
		    $4, $5, syscall, $6) > sysent
		printf("\t\"old.%s\",\t\t/* %d = old %s */\n", \
		    $6, syscall, $6) > sysnames
		printf("#define\tSYS_o%s\t%d\n", \
		    $6, syscall) > syshdr
		printf("\t\t\t\t/* %d is old %s */\n", \
		    syscall, comment) > syshdr
		syscall++
		next
	}
	$2 == "LIBCOMPAT" {
		printf("int\to%s();\n", $5) > syscompat
		printf("\tcompat(%d,%s),\t\t/* %d = old %s */\n", \
		    $4, $5, syscall, $6) > sysent
		printf("\t\"old.%s\",\t\t/* %d = old %s */\n", \
		    $6, syscall, $6) > sysnames
		printf("#define\tSYS_%s\t%d\t/* compatibility; still used by libc */\n", \
		    $6, syscall) > syshdr
		syscall++
		next
	}
	$2 == "OBSOL" {
		printf("\t0, nosys,\t\t\t/* %d = obsolete %s */\n", \
		    syscall, comment) > sysent
		printf("\t\"obs_%s\",\t\t\t/* %d = obsolete %s */\n", \
		    $5, syscall, comment) > sysnames
		printf("\t\t\t\t/* %d is obsolete %s */\n", \
		    syscall, comment) > syshdr
		syscall++
		next
	}
	$2 == "UNIMPL" {
		printf("\t0, nosys,\t\t\t/* %d = %s */\n", \
		    syscall, comment) > sysent
		printf("\t\"#%d\",\t\t\t/* %d = %s */\n", \
		    syscall, syscall, comment) > sysnames
		syscall++
		next
	}
	{
		printf "%s: line %d: unrecognized keyword %s\n", infile, NR, $2
		exit 1
	}
	END {
		printf("\n#else /* %s */\n", compat) > syscompat
		printf("#define compat(n, name) 0, nosys\n") > syscompat
		printf("#endif /* %s */\n\n", compat) > syscompat

		printf("};\n\n") > sysent
		printf("int\tnsysent = sizeof(sysent) / sizeof(sysent[0]);\n") > sysent

		printf("};\n") > sysnames
	} '
echo
cat $sysdcl $syscompat $sysent >$syssw

cat $emldcl $emlent > $syse

cat >> $syse <<+EOF+ #------------------------------------------------------
};

int	nsysent = sizeof(sysent)/sizeof(struct sysent);

struct sysent   sysent_task_by_pid =
        syss(bsd_task_by_pid, 1);

struct sysent   sysent_pid_by_task =
        syss(bsd_pid_by_task, 4);

struct sysent   sysent_htg_ux_syscall =
        sysr(e_htg_syscall);

struct sysent   sysent_init_process =
        syss(bsd_init_process, 1);

+EOF+

chmod 444 $sysnames $syshdr $syssw