#include <iostream>
using namespace std;


string cipherRailfence(string plaintext, int key){
	int i, j;
	int row = 0, col = 0, recuo = -1;
	int textlen;
	std::string cipheredtext;

	// declaracoes apos saber o tamanho do plaintext
	textlen = plaintext.length();
	char railfence[key][textlen];

	// zera a matriz de railfence
	for (i = 0 ; i < key ; i++){
    	for (j = 0 ; j < textlen ; j++){
			railfence[i][j] = '\0';
    	}
	}
	// faz o ziguezague
	for (i = 0; i < textlen; ++i){
        railfence[row][col++] = plaintext[i];
        //analisa quando faz o desvio
        if(row == 0 || row == key-1) 
            recuo = recuo * (-1);
        row = row + recuo;
    }
    // insere apenas os caracteres validos na string
	for (i = 0 ; i < key ; i++){
    	for (j = 0 ; j < textlen ; j++){
    		if (railfence[i][j] != '\0')
				cipheredtext.append(1, railfence[i][j]);
    	}
	}
	return cipheredtext;
}

string decipherRailfence(string cipheredtext, int key){
	int i, j, k = 0;
	int row = 0, col = 0, recuo = -1;
	int textlen;
	std::string plaintext;

	// declaracoes apos saber o tamanho do plaintext
	textlen = cipheredtext.length();
	char railfence[key][textlen];


	// zera a matriz de railfence
	for (i = 0 ; i < key ; ++i){
    	for (j = 0 ; j < textlen ; ++j){
			railfence[i][j] = '\0';
    	}
	}
	// colore o ziguezague que foi usado para criptografar
	for (i = 0; i < textlen; ++i){
        railfence[row][col++] = 1;
        //analisa quando faz o desvio
        if((row == 0) || (row == key-1)) 
            recuo = recuo * (-1);
        row = row + recuo;
    }

    // insere nas celulas coloridas da matriz o texto cifrado
    for (i = 0 ; i < key ; ++i){ 
    	for (j = 0 ; j < textlen ; ++j){
    		if (railfence[i][j] == 1){
    			railfence[i][j] = cipheredtext[k];
    			k++;
    		}
    	}
    }

    // reordena na string os caracteres
    row = col = 0;
    recuo = -1;
    for (i = 0; i < textlen; ++i){
        plaintext.append(1, railfence[row][col++]);
        //analisa quando faz o desvio
        if(row == 0 || row == key-1) 
            recuo = recuo * (-1);
        row = row + recuo;
    }
    return plaintext;
}

int main(int argc, char *argv[]){
	int key = 4;
	std::string plaintext;
	std::string cipheredtext;

	// entra com o plaintext
	std::getline (std::cin, plaintext);

	cipheredtext = cipherRailfence(plaintext, key);
	std::cout << cipheredtext << endl;


	plaintext = decipherRailfence(cipheredtext, key);
	std::cout << plaintext << endl;
}
