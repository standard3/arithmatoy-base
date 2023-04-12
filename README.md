# Maths 2600 - Représentation et formalisation des nombres

Ce repository de code accompagne la première session de cours de mathématiques de [l'école de cybersécurité 2600](https://candidature.ecole2600.com/).

Les slides de cours sont disponible ici: https://c2ba-learning.gitlab.io/maths/maths-2600-slides-nombres/1

## Exercices de TP

Plusieurs exercices sont à réaliser pendant le cours / TP et seront notés.

Ces exercices en python sont à réaliser dans `tests/tp.py`. Le fichier `tests/test_tp.py` contient des tests automatiques qui seront utilisés pour vous noter, et ne doit pas être modifié.

Il est interdit d'utiliser des `import` dans le fichier `tests/tp.py`, tout votre code doit être from scratch.

Pour mettre en place votre environnement de développement python:

- Créez un environnement virtuel python: `python -m venv .venv`
- Activez le:
  - `source .venv/bin/activate` sous Linux / Mac
  - `source .venv/scripts/activate` sous Windows
- Installez `pytest` dans le venv: `python -m pip install pytest`
- Executez les tests de TP: `python -m pytest tests/test_tp.py`

Ces tests doivent échouer la première fois, et passer une fois votre implémentation terminée.

Vous pouvez lancer un seul test du fichier avec la commande `python -m pytest tests/test_tp.py -k NOM_DU_TEST`.

Dans l'ordre des exercices à faire en TP:

```bash
python -m pytest tests/test_tp.py -k test_nombre_entier
python -m pytest tests/test_tp.py -k test_successeur
python -m pytest tests/test_tp.py -k test_addition
python -m pytest tests/test_tp.py -k test_multiplication
python -m pytest tests/test_tp.py -k test_facto_ite
python -m pytest tests/test_tp.py -k test_facto_rec
python -m pytest tests/test_tp.py -k test_fibo_rec
python -m pytest tests/test_tp.py -k test_fibo_ite
```

Pour débugguer vous pouvez mettre des `print` dans vos tests et lancer avec l'option `-s`, par exemple: `python -m pytest tests/test_tp.py -k test_nombre_entier -s`

Vous pouvez également lancer python en interactif sur le fichier: `python -im tests.tp`. Vous pouvez alors appeler vos fonctions.

Pour une meilleure experience interactive, vous pouvez également installer `ipython` sur votre système, le lancer puis utiliser la commande `%run tests/tp.py` pour charger/recharger votre script et appeler ses fonctions interactivement.

## Projet - Arithmatoy

