# 🎮 CHEAT SHEET - Raycasting 3D en Une Page

## 📌 Concept Essentiel
Le **raycasting** simule un monde 3D en tirant un rayon pour chaque pixel.
```
Pour chaque pixel X:
  Rayon = Position du joueur + Direction × paramètre(X)
  Jusqu'à toucher un mur → Calculer hauteur → Dessiner
```

---

## 👤 Caméra du Joueur

| Variable | Sens | Exemple |
|----------|------|---------|
| `player_x, player_y` | Position dans la grille 2D | (5.5, 5.5) |
| `dir_x, dir_y` | Direction de visée (normalisée) | (1.0, 0.0) |
| `plane_x, plane_y` | Plan caméra (perpendiculaire) | (0.0, 0.66) |

---

## 🔫 Les 7 Étapes du Raycasting (Pour 1 Pixel)

### 1️⃣ **Préparation du Rayon** (`prep_rayon`)
```c
camera_x = 2 * x / 800.0 - 1;  // -1.0 à +1.0
ray_dir_x = dir_x + plane_x * camera_x;
ray_dir_y = dir_y + plane_y * camera_x;
hypo_dist_x = fabs(1 / ray_dir_x);  // Distance unité X
hypo_dist_y = fabs(1 / ray_dir_y);  // Distance unité Y
```
**Résultat** : Direction du rayon pour ce pixel

### 2️⃣ **Configuration du Pas** (`step`)
```c
// Direction du mouvement
step_x = (ray_dir_x < 0) ? -1 : 1;
step_y = (ray_dir_y < 0) ? -1 : 1;

// Distance jusqu'à première grille
side_dist_x = distance à la prochaine ligne vertical;
side_dist_y = distance à la prochaine ligne horizontal;
```
**Résultat** : Direction et distances initiales

### 3️⃣ **Tracé DDA** (`dda`)
```c
map_x = player_x;  map_y = player_y;
while (world_map[map_y][map_x] != 1) {
    if (side_dist_x < side_dist_y) {
        side_dist_x += hypo_dist_x;
        map_x += step_x;
        side = 0;  // Collision en X
    } else {
        side_dist_y += hypo_dist_y;
        map_y += step_y;
        side = 1;  // Collision en Y
    }
}
```
**Résultat** : Position du mur + côté de collision

### 4️⃣ **Distance Perpendiculaire** (`wall_distance`)
```c
if (side == 0)
    wall_dist = side_dist_x - hypo_dist_x;
else
    wall_dist = side_dist_y - hypo_dist_y;
```
**Résultat** : Distance perpendiculaire (correction fish-eye)

### 5️⃣ **Hauteur de Ligne** (`calc_line`)
```c
line_height = (int)(600 / wall_dist);
draw_start = 300 - line_height / 2;
draw_end = 300 + line_height / 2;
// Contrôler les limites 0-599
```
**Résultat** : Pixels à colorer (haut et bas)

### 6️⃣ **Rendu Colonne** (`draw_column`)
```c
for (y = 0; y < 600; y++) {
    if (y < draw_start) pixel = CIEL;
    else if (y <= draw_end) pixel = MUR;
    else pixel = SOL;
}
```
**Résultat** : 1 colonne de 600 pixels colorée

### 7️⃣ **Répéter pour 800 Pixels** (`move`)
```c
clear_image();
for (x = 0; x < 800; x++) {
    prep_rayon(x);
    step();
    dda();
    wall_distance();
    calc_line();
    draw_column(x);
}
afficher_ecran();
```
**Résultat** : Image 3D complète (1 frame)

---

## 🎮 Gestion Clavier

```c
if (key == 119) {  // W
    player_x += dir_x * 0.1;
    player_y += dir_y * 0.1;
}
if (key == 115) {  // S
    player_x -= dir_x * 0.1;
    player_y -= dir_y * 0.1;
}
if (key == 100) {  // D (tourner droit)
    angle = 0.1 rad;
    appliquer_rotation(angle);
}
if (key == 97) {   // A (tourner gauche)
    angle = -0.1 rad;
    appliquer_rotation(angle);
}
```

---

## 🔄 Rotation Matricielle 2D

```c
// Original (ne pas modifier durant calcul)
old_dir_x = dir_x;

// Nouvelle direction
dir_x = dir_x * cos(angle) - dir_y * sin(angle);
dir_y = old_dir_x * sin(angle) + dir_y * cos(angle);

// Même chose pour plane (le perpendiculaire)
```

---

## 📊 Structure de Données Principale

```c
typedef struct s_cube {
    // Graphique
    void *mlx;      // Contexte MiniLibX
    void *win;      // Fenêtre
    t_data img;     // Image (pixels)
    
    // Caméra
    double player_x, player_y;  // Position
    double dir_x, dir_y;        // Direction
    double plane_x, plane_y;    // Plan
    
    // Rayon Actuel
    double ray_dir_x, ray_dir_y;    // Direction rayon
    double camera_x;                // Position X caméra (-1 à 1)
    double hypo_dist_x, hypo_dist_y;  // Distances unités
    double side_dist_x, side_dist_y;  // Distances initiales
    
    // DDA
    int step_x, step_y;     // Direction pas
    int map_x, map_y;       // Position grille
    int side;               // 0=X, 1=Y
    
    // Résultat
    double wall_dist;       // Distance au mur
    int line_height;        // Hauteur pixels
    int draw_start, draw_end;  // Limites Y
} t_cube;
```

---

## 🎨 Couleurs

```c
0x0087FF  // Ciel (bleu)
0x8B4513  // Mur (marron)
0xDEB887  // Sol (beige)
```

---

## 🌍 Grille du Monde

```c
int world_map[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},  // 1=mur, 0=vide
    {1,0,0,1,1,0,0,0,0,1},
    // ...
};
```

---

## 📐 Formules Clés

| Formule | Signification |
|---------|---------------|
| `camera_x = 2*x/800 - 1` | Normaliser X pixel à [-1, 1] |
| `ray = dir + plane*camera_x` | Calculer rayon pour pixel |
| `hypo_dist = \|1/ray_dir\|` | Distance pour franchir une grille |
| `line_height = 600/distance` | Hauteur basée sur distance |
| `draw_height = 600 - line_height` | Hauteur ciel & sol |

---

## 🚀 Points Clés à Retenir

✅ **DDA** : Parcourir grille très efficacement  
✅ **Distance perpendiculaire** : Correction du fish-eye  
✅ **Perspective** : Plus loin = plus petit  
✅ **Boucle** : 800 × ~5-10 itérations DDA = ~4000-8000 cellules/frame  
✅ **Vitesse** : Raycasting 2.5D c'est TRÈS rapide!

---

## ⚙️ Paramètres Modifiables

```c
// Vitesse
move_speed = 0.1;      // Distance par pression clé
rot_speed = 0.1;       // Radians par pression clé

// Écran
SCREEN_WIDTH = 800;    // Résolution X
SCREEN_HEIGHT = 600;   // Résolution Y

// Caméra
plane_length = 0.66;   // FOV (plus grand = FOV plus large)
```

---

## 🐛 Erreurs Courantes

| Erreur | Cause | Solution |
|--------|-------|----------|
| Déformation visuelle | Pas d'utilisation de wall_dist | Utiliser distance perpendiculaire |
| Murs qui sautillent | Collision pendant déplacement | Ajouter détection collision |
| Rotation lente | Angle pas en radians | Convertir en radians |
| Écran noir | MiniLibX pas initialisé | Vérifier mlx_init() |

---

## 📚 Ressources Externes

- **Raycasting Game Engine**: https://en.wikipedia.org/wiki/Raycasting
- **Wolfenstein 3D**: Jeu historique (1992, gratuit maintenant)
- **Lodev.org**: Excellent tutoriel raycasting

---

**Mémoriser cette page = Comprendre le raycasting! 🚀**
