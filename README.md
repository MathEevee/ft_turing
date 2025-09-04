# 🤖 ft_turing

Une machine de Turing est un modèle théorique de calcul inventé par Alan Turing en 1936 : elle se compose d’une bande infinie, d’une tête de lecture/écriture et d’un ensemble d’états qui dictent ses transitions. Elle sert de référence pour définir ce qui est calculable, en montrant qu’avec des règles simples on peut simuler n’importe quel algorithme. (https://fr.wikipedia.org/wiki/Machine_de_Turing).

Ce programme est une reproduction en OCaml de cette machine.

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

<img width="947" height="147" alt="Screenshot from 2025-09-04 15-12-58" src="https://github.com/user-attachments/assets/e5dde24b-1992-4405-b609-641f72635a4c" />

7. La liste de toutes les transitions
(Exemples : )


<img width="352" height="127" alt="Screenshot from 2025-09-04 15-15-37" src="https://github.com/user-attachments/assets/3fb7089d-c6a5-487f-910f-56c4c305d07c" />
<img width="352" height="127" alt="Screenshot from 2025-09-04 15-15-20" src="https://github.com/user-attachments/assets/b5b6d462-e043-4eab-a250-3b4ef650b80d" />

*************
8. Les différentes étapes du résultat

<img width="592" height="418" alt="Screenshot from 2025-09-04 15-20-06" src="https://github.com/user-attachments/assets/31062a4e-316a-4fa9-86f8-6ff2c8ed1084" />
