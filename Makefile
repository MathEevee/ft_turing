NAME = ft_turing

OBJS = Print Parsing Machine

MLI_FILES = Type.mli
MLI_FILES += $(OBJS:=.mli)

ML_FILES = main.ml
ML_FILES += $(OBJS:=.ml)

CMI_FILES = Type.cmi
CMI_FILES += $(OBJS:=.cmi)

CMO_FILES = main.cmo
CMO_FILES += $(OBJS:=.cmo)

O_FILES = main.o
O_FILES += $(OBJS:=.o)

CMX_FILES = main.cmx
CMX_FILES += $(OBJS:=.cmx)

OCAMLC = ocamlc
OCAMLOPT = ocamlopt
OCAMLDEP = ocamldep

CR = "\r"$(CLEAR)
CLEAR = "\033[0K"
BASENAME = `basename $@`

all: native

byte: $(NAME).occ

$(NAME).occ: $(CMI_FILES) $(CMO_FILES)
	@$(OCAMLC) -o $@ $^
	@printf $(CR)"\e[1m\e[38;5;74m>>> $(NAME).occ is created ! <<<\e[0m\n"

native: $(NAME).lopt

$(NAME).lopt: $(CMX_FILES)
	@$(OCAMLOPT) -o $@ $^
	@printf $(CR)"\e[1m\e[38;5;74m>>> $(NAME).lopt is created ! <<<\e[0m\n"

%.cmi: %.mli
	@$(OCAMLC) -c $<
	@printf $(CR)"\e[2m\e[38;5;32m>>>\e[0m $(BASENAME)%s \e[2m\e[38;5;32m<<<\e[0m"$(CLEAR)

%.cmo: %.ml
	@$(OCAMLC) -c $<
	@printf $(CR)"\e[2m\e[38;5;32m>>>\e[0m $(BASENAME)%s \e[2m\e[38;5;32m<<<\e[0m"$(CLEAR)

%.cmx: %.ml
	@$(OCAMLOPT) -c $<
	@printf $(CR)"\e[2m\e[38;5;32m>>>\e[0m $(BASENAME)%s \e[2m\e[38;5;32m<<<\e[0m"$(CLEAR)

%.o: %.ml
	@$(OCAMLOPT) -c $<
	@printf $(CR)"\e[2m\e[38;5;32m>>>\e[0m $(BASENAME)%s \e[2m\e[38;5;32m<<<\e[0m"$(CLEAR)

depend:
	@$(OCAMLDEP) $(ML_FILES) $(MLI_FILES) > .depend

-include .depend

clean:
	@rm -f $(CMO_FILES) $(CMI_FILES) $(CMX_FILES) $(O_FILES) .depend
	@printf "\e[1m\e[38;5;29mAll object files of $(NAME) are cleaned !\e[0m\n"

fclean: clean
	@rm -rf $(NAME).occ
	@rm -rf $(NAME).lopt
	@printf "\e[1m\e[38;5;36m$(NAME) is cleaned !\e[0m\n"

re : fclean all

reocc : fclean byte

.PHONY: all clean fclean re depend native byte
