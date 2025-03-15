# Projeto-PBM
Projeto acadêmico em C que codifica imagens binárias em arquivos PBM ou por dados informados manualmente

O processo de codificação é essencialmente simples, sendo constituído de duas regras apenas e que são 
descritas a seguir: 
  1. Se uma imagem é uniforme, possuindo todos os pixels de uma mesma cor, o código gerado para ela será 
dado simplesmente pela letra correspondente a cor de seus pixels. Por exemplo, se uma imagem for toda 
branca, o código resultante é B (branco); e no caso a imagem seja toda preta, o código corresponderá a 
letra P (preto). 
  2. No entanto é possível que a imagem apresente pixels de cores diversificadas. Neste caso, o código emitido 
na saída será dado pela letra X e, dois cortes, um horizontal e outro vertical, são realizados produzindo 
até quatro subimagens. 

Cada corte é realizado aproximadamente no ponto médio da imagem, dividindo a imagem na metade. 
Após ambos os cortes serem realizados, o processo então continua com a analisa cada uma das 
subimagens, completando o código com o resultado do processamento do 1º, 2º, 3º e 4º quadrantes, 
nesta ordem. 

# Exemplos passo a passo
Considere que o grid dado pela Figura 1 represente uma imagem binária de dimensões 3x5, onde os elementos escuros 
correspondem a pixels pretos e as que são dadas em claro como sendo pixels brancos. 
![image](https://github.com/user-attachments/assets/cfb70f02-8aea-4a14-9f78-6064abbacd07)

Como a imagem não é homogênea é geramos um código X e realizamos os dois cortes, dividindo a imagem 
em quatro partes. Observe não é permitido ter “meios pixels”, então a quantidade maior de colunas ficará 
para a metade à esquerda; e a quantidade maior de linhas para a metade de cima. A Figura 2 ilustra os pontos 
de corte e as quatro subimagens resultantes do processo de divisão. 
![image](https://github.com/user-attachments/assets/c057ea85-f0a2-44f4-bcb5-68609106453e)

O processo de codificação deve continuar analisando cada uma das subimagens resultantes segundo a ordem 
de seus quadrantes. O código desta imagem será dado então pela letra X seguida da concatenação dos códigos 
resultantes da análise de cada uma das subimagens. 
Para a subimagem do 1º quadrante, que também não é homogênea, teremos a emissão de um X e a divisão 
em 4 partes, ficando da seguinte forma: 
![image](https://github.com/user-attachments/assets/5135d6cb-f0c9-488d-a2ed-6d2e9d7e57bc)

1º quadrante contém apenas pixels pretos e o resultado da sua codificação resultará em P. Em seguida, processamos a subimagem 
correspondente ao 2º quadrante e cujo resultado será B, dado que é uma imagem formada apenas por um 
pixel branco. Para o 3º quadrante, assim como no caso do 1º, o código será P; e para o 4º quadrante, teremos um B. 
Assim, até o presente instante, o código parcial para a imagem inicial será X seguido de XPBPB (do 1º quadrante) concatenado com o código resultante do processamento dos demais quadrantes (2º, 3º e 4º). 

Vai repetir esse processo com cada quadrante cortado no primeiro passo, até todos estiverem homogeneos, fortmando assim, o seguinte código:
![image](https://github.com/user-attachments/assets/1af1b8bc-ba25-4e92-950e-6f56f4c61f42)




# Exemplos Completos:
![image](https://github.com/user-attachments/assets/c7911fe5-44e6-4bcf-b120-82521cce696b)
