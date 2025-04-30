/*
2opt(tableau, start, end, profondeur)
    si profondeur > 0
        pour i de start à end
            inverser(tableau, start, i) // Inverser le segment [start, i]
            si coût(tableau) < meilleur_coût
                meilleur_coût = coût(tableau)
                meilleure_solution = tableau
            2opt(tableau, i, end, profondeur - 1)
            inverser(tableau, start, i) // Restaurer le tableau (backtracking)
            
*/