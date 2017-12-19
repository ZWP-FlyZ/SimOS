IPL_MAKE_PATH	=	./src/ipl/#   IPL的makefile路径

MAKE	=	make -r

ipl : 
	$(MAKE) -C $(IPL_MAKE_PATH) bin



