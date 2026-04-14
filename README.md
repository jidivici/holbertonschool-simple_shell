# holbertonschool-simple_shell

# Simple Shell

## Description

Le projet Simple Shell consiste à recréer un interpréteur de commandes minimal similaire à un shell Unix comme sh ou bash.

Ce programme lit les commandes entrées par l’utilisateur, les analyse (parsing), puis les exécute en utilisant les appels système appropriés (fork, execve, wait, etc.).

---

## Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

---

## Utilisation

Mode interactif :
./hsh

Mode non interactif :
echo "ls -l" | ./hsh

---

## Fonctionnement global

1. Afficher un prompt
2. Lire l’entrée utilisateur
3. Parser la ligne (tokenization)
4. Vérifier si c’est une builtin
5. Sinon :
    - Chercher le chemin via PATH
    - Créer un processus avec fork
    - Exécuter avec execve
6. Attendre la fin du processus avec wait

---

## Gestion des cas possibles

### 1. Entrée utilisateur

Cas valides :
- ls
- ls -l /tmp
- /bin/ls
- echo hello

Cas à gérer :
- Entrée vide ("")
- Chaîne contenant uniquement des espaces
- EOF (Ctrl + D)

Comportement attendu :
- Ignorer les entrées vides
- Quitter proprement sur EOF

---

### 2. Parsing (tokenization)

Cas valides :
- "ls -l" devient ["ls", "-l"]
- "echo hello world" devient ["echo", "hello", "world"]

Cas limites :
- Multiples espaces (ex: "ls     -l")
- Tabs et retours à la ligne

Solution :
- Utiliser strtok avec les délimiteurs " \t\r\n"

---

### 3. Builtins

Builtins obligatoires :

exit
- Quitte le shell
- Peut prendre un argument (ex: exit 98)
- Retourne le bon code de sortie

env
- Affiche toutes les variables d’environnement

---

### 4. Résolution du PATH

Cas valides :
- ls doit être trouvé dans /bin/ls ou /usr/bin/ls

Cas à gérer :
- Commande inexistante (ex: fakecmd)
- PATH vide ou NULL
- Commande contenant déjà un chemin (ex: /bin/ls)

Comportement attendu :
- Si la commande contient "/", ne pas chercher dans PATH
- Sinon, parcourir PATH et tester chaque dossier

En cas d’échec :
./hsh: 1: fakecmd: not found

---

### 5. Exécution (fork + execve)

Cas valides :
- Commande existante
- Permissions correctes

Cas à gérer :
- fork échoue
- execve échoue
- Permission refusée

Comportement :
- fork crée un processus enfant
- execve remplace l’image du processus
- le parent attend avec wait ou waitpid

---

### 6. Gestion des erreurs

Cas à gérer :
- Commande inconnue
- Mauvais arguments
- Erreurs système

Exemples :
./hsh: 1: lszzz: not found
Permission denied

Le programme ne doit pas crash

---

### 7. Gestion de la mémoire

À vérifier :
- Libérer la mémoire après chaque commande
- Éviter les memory leaks
- Free correctement les tableaux de strings

Fonctions utiles :
- free
- malloc
- strdup

---

### 8. Variables d’environnement

Fonctionnalités :
- Accéder à PATH via getenv ou env
- Utiliser execve avec env

Cas à gérer :
- PATH inexistant
- Variables mal formées

---

### 9. Mode interactif vs non interactif

Interactif :
- Affiche un prompt
- Attend les entrées utilisateur

Non interactif :
- Lit depuis stdin (pipe ou fichier)
- N’affiche pas de prompt

---

### 10. Cas avancés (optionnels selon projet)

- Gestion des signaux (Ctrl + C)
- Gestion des pipes (|)
- Redirections (>, <, >>)
- Variables ($HOME, $PATH)
- Historique des commandes

---

## Contraintes

- Utiliser uniquement les fonctions autorisées
- Respecter la norme de code
- Pas de memory leaks
- Code modulaire et lisible

---

## Auteurs

Projet réalisé dans le cadre de la formation en programmation système.
