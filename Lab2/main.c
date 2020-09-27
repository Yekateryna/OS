#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "env.h"

 int main(int argc,char* argv[])
 {
	if (argc == 1)
	{
		env_info();
	}
	else
	{
		extern char* optarg;
		char* optstring = "hi:s:a:v:d:c";

		int c;
 		struct option long_opt[] = {
 			{"help",0,0,'h'},
 			{"info",1,0,'i'},
 			{"set",1,0,'s'},
 			{"assign",1,0,'a'},
 			{"value",1,0,'v'},
 			{"del",1,0,'d'},
 			{"clear",0,0,'c'},
 			{NULL,0,NULL,0}
 		};

 		char* assign = NULL;
 		char* value = NULL;

 		while((c = getopt_long(argc,argv,optstring,long_opt,NULL))!=-1)
 		{
 			switch(c)
 			{
 				case 'h':
 					help();
 					return 0;
 				
 				case 'i':
 					get_info(optarg);
 					return 0;

 				case 's':
 					set_value(optarg);
 					return 0;

 				case 'a':
 					assign = optarg;
 				break;
 				

 				case 'v':
 					value = optarg;
 				break;

 				case 'd':
 					del(optarg);
 					return 0;

 				case 'c':
 					clear();
 					return 0;

 				default:
 					help();
 					return 0;
 			}
 		}
 		printf("assign = %s, value = %s\n",assign,value );
 		put(assign,value);
	}
 	return 0;
 }