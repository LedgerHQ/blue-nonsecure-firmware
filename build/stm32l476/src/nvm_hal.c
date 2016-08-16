/*******************************************************************************
*   Ledger Blue - Non secure firmware
*   (c) 2016 Ledger
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
********************************************************************************/

#include "stm32l4xx.h"

#include "nvm.h"


#ifdef NVM_PAGE_SIZE_B
extern const unsigned char * nvm_write_page_address;

/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t Addr)
{
  uint32_t page = 0;
  
  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
  }
  
  return page;
}

/**
  * @brief  Gets the bank of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The bank of a given address
  */
static uint32_t GetBank(uint32_t Addr)
{
  uint32_t bank = 0;
  
  if (READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_FB_MODE) == 0)
  {
    /* No Bank swap */
    if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_1;
    }
    else
    {
      bank = FLASH_BANK_2;
    }
  }
  else
  {
    /* Bank swap */
    if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_2;
    }
    else
    {
      bank = FLASH_BANK_1;
    }
  }
  
  return bank;
}

void nvm_write_flush(void) {
  unsigned int page = nvm_write_page_address;
  // small basic check
  if (!nvm_write_page_address) {
    return;
  }

  // BEGIN HAL
  
  HAL_FLASH_Unlock();

  /* Clear OPTVERR bit set on virgin samples */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
  /* Fill EraseInit structure*/
  FLASH_EraseInitTypeDef EraseInitStruct;
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Banks       = GetBank(page);
  EraseInitStruct.Page        = GetPage(page);
  EraseInitStruct.NbPages     = 1;

  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
     you have to make sure that these data are rewritten before they are accessed during code
     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
     DCRST and ICRST bits in the FLASH_CR register. */
  unsigned int PAGEError;
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK) {
    // TODO : Halt, catch fire, explode 
    for(;;);
  }

  const unsigned long long int* page_dword = page;
  const unsigned long long int* buffer_dword = nvm_page_D;
  while ((unsigned int)buffer_dword < ((unsigned int)nvm_page_D)+sizeof(nvm_page_D)) {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, page_dword, *buffer_dword) != HAL_OK)
    {
      // TODO : Halt, catch fire, explode 
    }
    buffer_dword++;
    page_dword++;
  }

  /* not yet working
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST_AND_LAST, page, nvm_page_D);
  */

  if (memcmp(page, nvm_page_D, NVM_PAGE_SIZE_B) != 0) {
    for(;;);
  } 

  HAL_FLASH_Lock();

  // END HAL

  nvm_write_page_address = NULL;
}
#endif // NVM_PAGE_SIZE_B
