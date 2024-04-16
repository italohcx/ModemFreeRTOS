/*
 * cfg_files.c
 *
 *  Created on: Mar 15, 2024
 *      Author: italo
 */


#include "cfg_files.h"

#define MODBUS_MAP_FILE_PATH "modbus.map"


FILE *open_modbus_file(const char *mode) {

    FILE *file = file_open((char*) MODBUS_MAP_FILE_PATH, "ab+");
    if (!file) {
        printf("Erro ao abrir o arquivo %s.\n", MODBUS_MAP_FILE_PATH);
    }
    return file;
}

void close_modbus_file(FILE *file) {
    if (file) {

    	file_close(file);
    }
}



// Função para salvar a estrutura MB no arquivo
cfg_file_status_t save_mb_to_file(const MB *mb) {
    // Abra o arquivo para escrita binária
    FILE_POINTER file = open_modbus_file("wb");

    if (!file) {
        return CfgFiles_error_unknownError;
    }

    // Escreva a estrutura MB no arquivo
    size_t bytes_written = fwrite(mb, sizeof(MB), 1, file);

    if (bytes_written != 1) {

    	printf("Erro ao escrever no arquivo.\n");
        close_modbus_file(file);
        return CfgFiles_error_unknownError;
    }

    // Feche o arquivo
    close_modbus_file(file);

    printf("Dados salvos com sucesso no arquivo modbus.map.\n");

    return CfgFiles_success;
}


cfg_file_status_t load_mb_from_file(MB *mb) {
    // Abra o arquivo para leitura binária
    FILE_POINTER file = open_modbus_file("rb");
    if (!file) {
        return CfgFiles_error_unknownError;
    }

    // Leia os dados do arquivo para a estrutura MB
    size_t bytes_read = fread(mb, sizeof(MB), 1, file);
    if (bytes_read != 1) {
        printf("Erro ao ler do arquivo.\n");
        close_modbus_file(file);
        return CfgFiles_error_unknownError;
    }

    // Feche o arquivo
    close_modbus_file(file);

    printf("Dados carregados com sucesso do arquivo modbus.map.\n");

    return CfgFiles_success;
}










cfg_file_status_t write_to_mb_single_register(MB *mb, int index, uint16_t value)
{
    if (mb == NULL)
    {
        printf("Ponteiro para estrutura MB inválido.\n");
        return CfgFiles_error_invalidParameter;
    }

    // Verifica se o índice está dentro dos limites do array HOLDINGREGISTERS
    if (index < 0 || index >= TOTAL_VARIAVEIS_HOLDING)
    {
        printf("Índice de registro inválido.\n");
        return CfgFiles_error_invalidParameter;
    }

    // Abrir o arquivo correspondente aos registros no sistema de arquivos LittleFS
    FILE_POINTER file = open_modbus_file("rb+");
    if (!file)
    {
        printf("Erro ao abrir o arquivo.\n");
        return CfgFiles_error_fileOperationFailed;
    }

    // Calcular a posição do registro no arquivo
    int position = index * sizeof(uint16_t);

    // Posicionar o cursor do arquivo na posição do registro
    if (file_seek(file, position, SEEK_SET) != 0)
    {
        printf("Erro ao posicionar o cursor do arquivo.\n");
        file_close(file);
        return CfgFiles_error_fileOperationFailed;
    }

    // Escrever o valor no registro
    size_t bytes_written = file_write(&value, sizeof(uint16_t), 1, file);
    if (bytes_written != 1)
    {
        printf("Erro ao escrever no arquivo.\n");
        file_close(file);
        return CfgFiles_error_fileOperationFailed;
    }

    // Fechar o arquivo
    if (file_close(file) != 0)
    {
        printf("Erro ao fechar o arquivo.\n");
        return CfgFiles_error_fileOperationFailed;
    }

    return CfgFiles_success;
}




uint16_t read_from_mb_address(const MB *mb, int function_index, int array_index) {

    if (mb == NULL) {
        printf("Ponteiro para estrutura MB inválido.\n");
        return 0; // ou qualquer outro valor de erro
    }

    int total_array_sizes[4] = {TOTAL_VARIAVEIS_COILS, TOTAL_VARIAVEIS_INPUT, TOTAL_VARIAVEIS_HOLDING, TOTAL_VARIAVEIS_ESPELHO};

    if (function_index < 0 || function_index >= 4) {
        printf("Índice de função inválido.\n");
        return 0; // ou qualquer outro valor de erro
    }

    if (array_index < 0 || array_index >= total_array_sizes[function_index]) {
        printf("Índice de array inválido.\n");
        return 0; // ou qualquer outro valor de erro
    }

    FILE_POINTER file = file_open(MODBUS_MAP_FILE_PATH, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return 0; // ou qualquer outro valor de erro
    }

    int array_start_position = 0;
    for (int i = 0; i < function_index; i++) {
        array_start_position += sizeof(uint16_t) * total_array_sizes[i];
    }

    int position = array_start_position + sizeof(uint16_t) * array_index;

    if (file_seek(file, position, SEEK_SET) != 0) {
        printf("Erro ao posicionar o cursor do arquivo.\n");
        file_close(file);
        return 0; // ou qualquer outro valor de erro
    }

    uint16_t value;
    if (file_read(&value, sizeof(uint16_t), 1, file) != 1) {
        printf("Erro ao ler do arquivo.\n");
        file_close(file);
        return 0; // ou qualquer outro valor de erro
    }

    file_close(file);

    return value;
}
