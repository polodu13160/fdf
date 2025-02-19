import numpy as np

# Dimensions du tableau
rows, cols = 10, 10

# Génération d'un tableau de nombres aléatoires entre -59 et 59
data = np.random.randint(-59, 60, size=(rows, cols))

# Formatage des lignes pour garder un alignement uniforme
formatted_lines = [" ".join(f"{num:3d}" for num in row) for row in data]

# Nom du fichier
file_path = "./tableau_10000x10000.txt"

# Écriture dans un fichier
with open(file_path, "w") as f:
    f.write("\n".join(formatted_lines))

file_path
