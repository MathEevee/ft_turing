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

## 📍 Notes

Lors de l'exécution du programme avec un .json et un argument, on va avoir plusieurs informations par rapport au JSON :

1. Le nom de la machine 
2. L'alphabet que prend la machine
3. Le ou les caractère "blanc"

<img width="801" height="94" alt="Screenshot from 2025-09-04 15-11-05" src="https://github.com/user-attachments/assets/e678836a-e670-4e2d-9155-5706c0a0f11e" />

4. La liste de tous les noms d'états
5. L'état initial
6. Le ou les états finaux
7. La liste de toutes les transitions
*************
8. Les différentes étapes du résultat






