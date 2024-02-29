#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <string>
#include <vector>

#include <bfd.h>

#include "loader.h"


int
main(int argc, char *argv[])
{
  int option = 0, all = 0;
  size_t i;
  Binary bin;
  Section *sec;
  Symbol *sym;
  std::string fname;
  std::string sec_name_con;

  if(argc <= 2) {
  	if(strcmp( argv[1] , "--help" ) == 0 || strcmp( argv[1] , "-h" ) == 0) {
  	printf("Usage: %s <options> <binary>\n", argv[0]);
  	printf("Options:\n");
  	printf("  --help   Display this help message\n");
  	printf("  -h       Equivalent to --help\n");
  	printf("  -d       Display the loaded binary details\n");
  	printf("  -sec     Display the loaded sections info\n");
  	printf("  -sym     Display the loaded symbols info\n");
  	printf("  -all     Display all binary's info\n\n");
  	

  	printf("Usage: %s <options> <section> <binary>\n", argv[0]);
  	printf("Options:\n");
  	printf("  -con	   Display the content of the requested section\n");
 
  	return 1;

  	}
  	else {
  		printf("%s" ,argv[0]);
  		printf("Usage: %s <command> <binary>\n", argv[0]);
  	}
    return 1;
  }
  
  if 	 ( strcmp( argv[1], "-d"  ) == 0 ) { option = 1;}
  else if( strcmp( argv[1], "-sec") == 0 ) { option = 2;}
  else if( strcmp( argv[1], "-sym") == 0 ) { option = 3;}
  else if( strcmp( argv[1], "-con") == 0 ) { option = 4;}
  else if( strcmp( argv[1], "-all") == 0 ) { option = 1;  all = 1;}

  if(argc == 3) {  fname.assign(argv[2]); }
  else if (argc == 4) { sec_name_con = argv[2]; fname.assign(argv[3]); }
  if(load_binary(fname, &bin, Binary::BIN_TYPE_AUTO) < 0) {
    return 1;
  }

switch (option)
{
case 1:
  	 printf("loaded binary: '%s' %s/%s (%u bits) entry@0x%016jx \n\n", 
         bin.filename.c_str(), 
         bin.type_str.c_str(), bin.arch_str.c_str(), 
         bin.bits, bin.entry);
         if(all == 1) {goto all1;}
         break;
case 2:
all1:
	  printf("\nVirtual Adress       Size      Name                  Type\n");
	  printf("__________________________________________________________\n\n");
	  for(i = 0; i < bin.sections.size(); i++) {
	    sec = &bin.sections[i];
	    printf("  0x%016jx %-8ju %-20s   %s \n", 
	    sec->vma, sec->size, sec->name.c_str(), 
	    sec->type == Section::SEC_TYPE_CODE ? "CODE" : "DATA");
	    /*for (int j = 0; j < sec->size; j++) {
	    	printf("%02X ", sec->bytes[j]);
	    	if((j+1) % 16 ==0) {
	    		printf("\n");
	    	}
	    	if(sec->name == ".data") {
	    		printf("it workssssssss");
	    	}
	    }
	    printf("\n");*/
	  }
	  if(all == 1) {goto all2;}
	  break;

case 3:
all2:
  if(bin.symbols.size() > 0) {
    
    printf("\nscanned symbol tables:\n\n");
    printf("  Name                                     Address              Type\n");
    printf("_____________________________________________________________________\n\n");
    for(i = 0; i < bin.symbols.size(); i++) {
      sym = &bin.symbols[i];
      printf("  %-40s 0x%016jx   " ,sym->name.c_str(), sym->addr);
      if(sym->type & Symbol::SYM_TYPE_FUNC)  printf("FUNC\n");
      else if(sym->type & Symbol::SYM_TYPE_DATA)  printf("DATA\n");
      else if(sym->type & Symbol::SYM_TYPE_LOCAL)  printf("LOCAL\n");
      else if(sym->type & Symbol::SYM_TYPE_GLOBAL)  printf("GLOBAL\n");
    }
  }
  break;

case 4:
	 for(i = 0; i < bin.sections.size(); i++) {
	    sec = &bin.sections[i];
	    if(sec->name == sec_name_con) {
	    	for (int j = 0; j < sec->size; j++) {
	    		printf("%02X ", sec->bytes[j]); // Print hexadecimal value
			if ((j + 1) % 8 == 0) { // Print 8 characters in a line
		 		 printf("   "); // Add spacing for readability
		   		 for (size_t k = j - 7; k <= j; k++) { // Print ASCII representation
		       			 if (sec->bytes[k] >= 32 && sec->bytes[k] <= 126) {
		          			 printf("%c", sec->bytes[k]); // Printable characters
		       			 } else {
		            			 printf("."); // Non-printable characters
		        			}
		    		}
		   		printf("\n"); // Move to the next line
	       		}
    	 }
    	 // Print the remaining characters in the section if they are less than 8
    	 if (sec->size % 8 != 0) {
		// Add spacing to align ASCII representation
		for (size_t k = sec->size % 8; k < 8; k++) {
		    printf("    ");
		}
		// Print the remaining ASCII representation
		for (size_t k = sec->size - sec->size % 8; k < sec->size; k++) {
		    if (sec->bytes[k] >= 32 && sec->bytes[k] <= 126) {
		        printf("%c", sec->bytes[k]); // Printable characters
		    } else {
		        printf("."); // Non-printable characters
		    }
		}
		printf("\n"); // Move to the next line
	}
    	printf("\n"); // Add an empty line for readability
	}

	 }
   break;
   
   
default:
   printf("invalid option\n");
   break;
}
  unload_binary(&bin);

  return 0;
}

