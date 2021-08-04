all:
	make -C -f makefile_clean_all
	make -C -f makefile_exports
	make -C -f makefile_prx
	make -C -f makefile_pbp

prx:
	make -C -f makefile_prx
	
pbp:
	make -C -f makefile_pbp
	
kernel_prx:
	make -C -f makefile_prx_k
	
user_prx:
	make -C -f makefile_prx_u
	
exports:
	make -f makefile_exports
	
clean_all:
	make -C -f makefile_clean_all
	
backup:
	make -C -f makefile_backup
	
release:
	make -C -f makefile_release