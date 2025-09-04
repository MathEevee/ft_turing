# 🤖 ft_turing

Ce programme est en OCaml. Il a pour but de reproduire le fonctionnement de la machine de Turing (https://fr.wikipedia.org/wiki/Machine_de_Turing).

Pour expliquer, les .json vont représenter les engrenages de la machine, les .ml les rotations et changements d'états qui sont donnés dans les .json puis la bande de la machine de turing est passée en argument.

---

## 🚀 Lancer le programme

1. **Compiler** le programme :
   ```bash
   make
   ```
   (dans le dossier où se situe le `Makefile`)

2. **Exécuter** le programme :
   ```bash
   ./ft_turing.lopt <JSON> <arg>
   ex : ./ft_turing.lopt JSON/Palindrome.json "kayak"
   ```

---

