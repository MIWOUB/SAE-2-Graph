/*
2opt(____, min, max, profondreur)
    si profondeur > 0
        for(i)
            inverser(min, i)
            2opt(____, i, j, profondeur - 1)
            
*/