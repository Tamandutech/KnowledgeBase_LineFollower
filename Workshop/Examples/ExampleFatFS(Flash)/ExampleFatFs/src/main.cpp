// Espressif (ESP-IDF)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"

#include "esp_vfs.h"
#include "esp_vfs_fat.h"

#include "esp_log.h"

bool mounted = false;
extern "C"
{
  void app_main(void);
}

typedef struct
{
    int encmedia = 0;
    int status = 0;
    int regnum = 0;
}mapdata;

esp_err_t WriteData(uint8_t *data, size_t size)
{
    if(!mounted) return ESP_ERR_INVALID_STATE;
    FILE *f = fopen("/map/mapdata.txt", "w");
    if (f == NULL)
    {
        ESP_LOGE("Main", "Falha ao abrir arquivo mapdata.txt para escrita");
        return ESP_FAIL;
    }
    size_t bytesWriten = fwrite(data,size,1,f);
    bytesWriten = bytesWriten * size;
    if(bytesWriten != size)
    {
        ESP_LOGI("Main", "Escrito de mapdata.txt, %d bytes de % d, escrita falhada", bytesWriten, size);
        fclose(f);
        return ESP_FAIL;
    }
    ESP_LOGI("Main", "Escrito em mapdata.txt, %d bytes", bytesWriten);
    fclose(f);
    return ESP_OK;
}

esp_err_t ReadData(uint8_t * data, size_t size)
{
    if(!mounted) return ESP_ERR_INVALID_STATE;
    FILE *f = fopen("/map/mapdata.txt", "r");
    if (f == NULL)
    {
        ESP_LOGE("Main", "Falha ao abrir arquivo mapdata.txt para leitura");
        return ESP_FAIL;
    }
    size_t bytesReaden = fread(data,size,1,f);
    bytesReaden = bytesReaden * size;
    if(bytesReaden != size)
    {
        ESP_LOGI("Main", "lido de mapdata.txt, %d bytes de % d, leitura falhada", bytesReaden, size);
        fclose(f);
        return ESP_FAIL;
    }
    ESP_LOGI("Main", "lido de mapdata.txt, %d bytes, leitura sucedida", bytesReaden);
    fclose(f);
    return ESP_OK;
}

esp_err_t listflies(char * path)
{
    if(!mounted) return ESP_FAIL;
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    ESP_LOGI("Main", "Listando Arquivos do diretório /map");
    if(d)
    {
        while((dir = readdir(d)) != NULL)
        {
            ESP_LOGI("Main", "Arquivo: %s", dir->d_name);
        }
        closedir(d);
    }
    return ESP_OK;
}

void app_main() 
{
    esp_log_level_set("Main", ESP_LOG_INFO);
    wl_handle_t s_wl_handle = WL_INVALID_HANDLE;
    esp_vfs_fat_sdmmc_mount_config_t mount_config;
    mount_config.format_if_mount_failed = true;
    mount_config.max_files = 5;
    mount_config.allocation_unit_size = CONFIG_WL_SECTOR_SIZE;
    esp_err_t err = esp_vfs_fat_spiflash_mount("/map", "storage", &mount_config, &s_wl_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE("Main", "Falha ao montar FATFS (%s)", esp_err_to_name(err));
        mounted = false;
    }
    else
    {
        ESP_LOGI("Main", "FATFS montado com sucesso em /map");
        mounted = true;
    }
    listflies((char *)"/map");

    mapdata regData;
    regData.encmedia = 500;
    regData.status = 0;
    regData.regnum = 1;
    for(;;)
    {
        uint8_t * dataSave = (uint8_t*) malloc(sizeof(regData));
        esp_err_t ret = ReadData(dataSave, sizeof(regData));
        if(ret == ESP_OK)
        {
            memcpy(&regData, dataSave, sizeof(regData));
            ESP_LOGI("Main", "Registro: %d\nEncMedia:%d\nStatus:%d", regData.regnum,regData.encmedia,regData.status);
            regData.regnum++;
            regData.encmedia += 500;
            regData.status = regData.status ? 0 : 1;
            memcpy(dataSave, &regData, sizeof(regData));
            ret = WriteData(dataSave, sizeof(regData));
            if(ret == ESP_OK) ESP_LOGI("Main", "Dado escrito com sucesso");
            else ESP_LOGI("Main", "Falha ao escrever o dado");
        }
        else if(ret == ESP_FAIL)
        {
            memcpy(dataSave, &regData, sizeof(regData));
            ret = WriteData(dataSave, sizeof(regData));
            if(ret == ESP_OK) ESP_LOGI("Main", "Dado escrito com sucesso");
            else ESP_LOGI("Main", "Falha ao escrever o dado");
        }
        free(dataSave);
        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}