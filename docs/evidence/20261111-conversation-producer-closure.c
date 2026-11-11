/* Offline Windows 3.89.1 PE source closure; VA, image base 00400000. */


/* Extracted native producer 0040fc30; operand-closure */

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0040fc30(int param_1,byte *param_2,char param_3)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  char cVar8;
  char cVar9;
  char cVar10;
  char cVar11;
  char cVar12;
  char cVar13;
  FILE *_File;
  int iVar14;
  char *pcVar15;
  uint uVar16;
  byte *pbVar17;
  byte *pbVar18;
  char *pcVar19;
  byte bVar20;
  bool bVar21;
  bool bVar22;
  uint local_1914;
  char local_18e0 [1024];
  byte local_14e0 [1024];
  undefined4 local_10e0;
  undefined1 local_10dc;
  undefined4 local_ce0;
  undefined4 local_cdc;
  char local_8e0 [8];
  char local_8d8 [1016];
  char local_4e0 [1024];
  char local_e0 [104];
  char local_78 [108];
  uint local_c;
  undefined4 uStack_8;
  
  cVar8 = DAT_0a72b1bb;
  cVar6 = DAT_0a72b1ba;
  cVar13 = DAT_0a72b1b7;
  cVar12 = DAT_0a72b1b6;
  cVar11 = DAT_0a72b1b5;
  cVar5 = DAT_0a72b1b2;
  cVar7 = DAT_0a72b1b1;
  cVar10 = DAT_0a72b1af;
  cVar3 = DAT_0a72b1ae;
  cVar4 = DAT_0a72b1ab;
  cVar2 = DAT_0a72b1aa;
  bVar20 = DAT_0a72a6f5;
  uStack_8 = 0x40fc3d;
  local_c = DAT_005e200c ^ (uint)&stack0xfffffffc;
  bVar22 = false;
  memset(local_14e0,0,0x400);
  memset(local_8e0,0,0x400);
  memset(&local_ce0,0,0x400);
  local_ce0 = DAT_0058f700;
  local_cdc = DAT_0058f704;
  pbVar17 = param_2;
  do {
    bVar1 = *pbVar17;
    pbVar17 = pbVar17 + 1;
  } while (bVar1 != 0);
  if (pbVar17 != param_2 + 1) {
    _File = fopen("ini_skills.txt","rt");
    if (_File == (FILE *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_004e6d20();
    }
    if (param_1 != -1) {
      param_1 = param_1 * 0x568;
      cVar2 = (&DAT_0615148b)[param_1];
      cVar3 = (&DAT_0615148d)[param_1];
      cVar4 = (&DAT_0615148e)[param_1];
      cVar5 = (&DAT_0615148f)[param_1];
      cVar6 = (&DAT_0615148a)[param_1];
      cVar7 = (&DAT_0615148c)[param_1];
      cVar8 = (&DAT_06151490)[param_1];
      bVar20 = (&DAT_06151488)[param_1];
    }
    local_1914 = (uint)bVar20;
    local_18e0[0] = '!';
    local_18e0[1] = '\0';
    iVar14 = feof(_File);
    if (iVar14 == 0) {
LAB_0040fe20:
      FUN_004d4280();
      if (local_4e0[0] != '.') goto LAB_0040fe99;
      pcVar15 = (char *)FUN_0055fb00();
      pcVar19 = pcVar15;
      do {
        cVar9 = *pcVar19;
        pcVar19[(int)(local_14e0 + -(int)pcVar15)] = cVar9;
        pcVar19 = pcVar19 + 1;
      } while (cVar9 != '\0');
      pbVar17 = local_14e0;
      pbVar18 = param_2;
      do {
        bVar20 = *pbVar17;
        bVar21 = bVar20 < *pbVar18;
        if (bVar20 != *pbVar18) {
LAB_0040fe90:
          uVar16 = -(uint)bVar21 | 1;
          goto LAB_0040fe95;
        }
        if (bVar20 == 0) break;
        bVar20 = pbVar17[1];
        bVar21 = bVar20 < pbVar18[1];
        if (bVar20 != pbVar18[1]) goto LAB_0040fe90;
        pbVar17 = pbVar17 + 2;
        pbVar18 = pbVar18 + 2;
      } while (bVar20 != 0);
      uVar16 = 0;
LAB_0040fe95:
      if (uVar16 != 0) goto LAB_0040fe99;
      bVar22 = true;
      iVar14 = 0;
      do {
        pcVar19 = local_4e0 + iVar14;
        *(char *)((int)&local_ce0 + iVar14) = *pcVar19;
        iVar14 = iVar14 + 1;
      } while (*pcVar19 != '\0');
      local_10e0 = DAT_0058f73c;
      local_10dc = DAT_0058f740;
      while( true ) {
        memset(local_4e0,0,0x400);
        FUN_004d4280();
        pcVar19 = local_4e0;
        do {
          cVar9 = *pcVar19;
          pcVar19 = pcVar19 + 1;
        } while (cVar9 != '\0');
        if ((pcVar19 == local_4e0 + 1) || (iVar14 = feof(_File), iVar14 != 0)) break;
        pcVar19 = strstr(local_4e0,"ATTRIBS");
        if (pcVar19 != (char *)0x0) {
          pcVar15 = (char *)FUN_0055fc00();
          pcVar19 = pcVar15;
          do {
            cVar9 = *pcVar19;
            pcVar19[(int)(local_8e0 + -(int)pcVar15)] = cVar9;
            pcVar19 = pcVar19 + 1;
          } while (cVar9 != '\0');
        }
        pcVar19 = strstr(local_4e0,"GROUP");
        if (pcVar19 != (char *)0x0) {
          pcVar15 = (char *)FUN_0055fc00();
          pcVar19 = pcVar15;
          do {
            cVar9 = *pcVar19;
            pcVar19[(int)&local_10e0 - (int)pcVar15] = cVar9;
            pcVar19 = pcVar19 + 1;
          } while (cVar9 != '\0');
        }
        pcVar19 = strstr(local_4e0,"KEY");
        if (pcVar19 != (char *)0x0) {
          pcVar15 = (char *)FUN_0055fc00();
          pcVar19 = pcVar15;
          do {
            cVar9 = *pcVar19;
            pcVar19[(int)(local_18e0 + -(int)pcVar15)] = cVar9;
            pcVar19 = pcVar19 + 1;
          } while (cVar9 != '\0');
        }
      }
    }
LAB_0040fea7:
    fclose(_File);
    if (bVar22) {
      if (param_3 == '\x03') {
        __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
        return;
      }
      pcVar19 = local_8e0;
      do {
        cVar9 = *pcVar19;
        pcVar19 = pcVar19 + 1;
      } while (cVar9 != '\0');
      if (pcVar19 == local_8e0 + 1) {
        local_8e0[0] = s_str_int_dex_0058f7a8[0];
        local_8e0[1] = s_str_int_dex_0058f7a8[1];
        local_8e0[2] = s_str_int_dex_0058f7a8[2];
        local_8e0[3] = s_str_int_dex_0058f7a8[3];
        local_8e0[4] = s_str_int_dex_0058f7a8[4];
        local_8e0[5] = s_str_int_dex_0058f7a8[5];
        local_8e0[6] = s_str_int_dex_0058f7a8[6];
        local_8e0[7] = s_str_int_dex_0058f7a8[7];
        local_8d8[0] = s_str_int_dex_0058f7a8[8];
        local_8d8[1] = s_str_int_dex_0058f7a8[9];
        local_8d8[2] = s_str_int_dex_0058f7a8[10];
        local_8d8[3] = s_str_int_dex_0058f7a8[0xb];
      }
      bVar20 = 0;
      iVar14 = 0;
      FUN_004d4430();
      do {
        if (DAT_06354bb0 == -1) {
LAB_00410315:
          if (iVar14 == 0) {
            iVar14 = 1;
          }
          ceil((double)(int)((longlong)(ulonglong)bVar20 / (longlong)iVar14));
          memset(local_e0,0,100);
          memset(local_4e0,0,0x400);
          if (local_1914 < 0xe) {
            pcVar19 = (&PTR_DAT_0058e354)[local_1914];
            pcVar15 = pcVar19;
            do {
              cVar2 = *pcVar15;
              pcVar15[(int)(local_e0 + -(int)pcVar19)] = cVar2;
              pcVar15 = pcVar15 + 1;
            } while (cVar2 != '\0');
          }
          pcVar15 = (char *)FUN_0055fc00();
          pcVar19 = pcVar15;
          do {
            cVar2 = *pcVar19;
            pcVar19[(int)(local_4e0 + -(int)pcVar15)] = cVar2;
            pcVar19 = pcVar19 + 1;
          } while (cVar2 != '\0');
          pcVar19 = local_4e0;
          do {
            cVar2 = *pcVar19;
            pcVar19 = pcVar19 + 1;
          } while (cVar2 != '\0');
          if (pcVar19 == local_4e0 + 1) {
            pcVar15 = (char *)FUN_0055fc00();
            pcVar19 = pcVar15;
            do {
              cVar2 = *pcVar19;
              pcVar19[(int)(local_4e0 + -(int)pcVar15)] = cVar2;
              pcVar19 = pcVar19 + 1;
            } while (cVar2 != '\0');
          }
          atoi(local_4e0);
          if (param_3 == '\0') {
            __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
            return;
          }
          if ((param_3 == '\x01') || (param_3 != '\x02')) {
            __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
            return;
          }
          pcVar15 = (char *)FUN_004d3db0();
          pcVar19 = pcVar15;
          do {
            cVar2 = *pcVar19;
            pcVar19[(int)(local_4e0 + -(int)pcVar15)] = cVar2;
            pcVar19 = pcVar19 + 1;
          } while (cVar2 != '\0');
          pcVar19 = strstr(local_4e0,"COMBAT");
          if (pcVar19 != (char *)0x0) {
            __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
            return;
          }
          strstr(local_4e0,"PHYSICAL");
          __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
          return;
        }
        if (DAT_06354bb0 == 0) {
          pcVar19 = &DAT_0634eb10;
        }
        else {
          pcVar19 = (char *)0x0;
        }
        _DAT_06354dbc = strtok(pcVar19,&DAT_06354dc4);
        if (_DAT_06354dbc == (char *)0x0) {
          DAT_06354bb0 = -1;
          goto LAB_00410315;
        }
        DAT_06354bb0 = DAT_06354bb0 + 1;
        pcVar19 = _DAT_06354dbc;
        do {
          cVar9 = *pcVar19;
          pcVar19[(int)(local_78 + -(int)_DAT_06354dbc)] = cVar9;
          pcVar19 = pcVar19 + 1;
        } while (cVar9 != '\0');
        iVar14 = iVar14 + 1;
        pcVar19 = strstr(local_78,"smt");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar5;
        }
        pcVar19 = strstr(local_78,"eye");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar11;
        }
        pcVar19 = strstr(local_78,"tch");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar12;
        }
        pcVar19 = strstr(local_78,"int");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar6;
        }
        pcVar19 = strstr(local_78,"dex");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar3;
        }
        pcVar19 = strstr(local_78,"str");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar2;
        }
        pcVar19 = strstr(local_78,"agi");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar4;
        }
        pcVar19 = strstr(local_78,"end");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar7;
        }
        pcVar19 = strstr(local_78,"wil");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar13;
        }
        pcVar19 = strstr(local_78,"hrg");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar8;
        }
        pcVar19 = strstr(local_78,"spd");
        if (pcVar19 != (char *)0x0) {
          bVar20 = bVar20 + cVar10;
        }
      } while( true );
    }
    pcVar19 = "SURVIVAL";
    pbVar17 = param_2;
    do {
      bVar20 = *pbVar17;
      bVar22 = bVar20 < (byte)*pcVar19;
      if (bVar20 != *pcVar19) {
LAB_00410052:
        uVar16 = -(uint)bVar22 | 1;
        goto LAB_00410057;
      }
      if (bVar20 == 0) break;
      bVar20 = pbVar17[1];
      bVar22 = bVar20 < (byte)pcVar19[1];
      if (bVar20 != pcVar19[1]) goto LAB_00410052;
      pbVar17 = pbVar17 + 2;
      pcVar19 = pcVar19 + 2;
    } while (bVar20 != 0);
    uVar16 = 0;
LAB_00410057:
    if (uVar16 != 0) {
      pcVar19 = "DAGGER";
      pbVar17 = param_2;
      do {
        bVar20 = *pbVar17;
        bVar22 = bVar20 < (byte)*pcVar19;
        if (bVar20 != *pcVar19) {
LAB_00410086:
          uVar16 = -(uint)bVar22 | 1;
          goto LAB_0041008b;
        }
        if (bVar20 == 0) break;
        bVar20 = pbVar17[1];
        bVar22 = bVar20 < (byte)pcVar19[1];
        if (bVar20 != pcVar19[1]) goto LAB_00410086;
        pbVar17 = pbVar17 + 2;
        pcVar19 = pcVar19 + 2;
      } while (bVar20 != 0);
      uVar16 = 0;
LAB_0041008b:
      if (uVar16 != 0) {
        pcVar19 = "RITUAL";
        pbVar17 = param_2;
        do {
          bVar20 = *pbVar17;
          bVar22 = bVar20 < (byte)*pcVar19;
          if (bVar20 != *pcVar19) {
LAB_004100c0:
            uVar16 = -(uint)bVar22 | 1;
            goto LAB_004100c5;
          }
          if (bVar20 == 0) break;
          bVar20 = pbVar17[1];
          bVar22 = bVar20 < (byte)pcVar19[1];
          if (bVar20 != pcVar19[1]) goto LAB_004100c0;
          pbVar17 = pbVar17 + 2;
          pcVar19 = pcVar19 + 2;
        } while (bVar20 != 0);
        uVar16 = 0;
LAB_004100c5:
        if (uVar16 != 0) {
          pcVar19 = "FLAIL";
          do {
            bVar20 = *param_2;
            bVar22 = bVar20 < (byte)*pcVar19;
            if (bVar20 != *pcVar19) {
LAB_004100f0:
              uVar16 = -(uint)bVar22 | 1;
              goto LAB_004100f5;
            }
            if (bVar20 == 0) break;
            bVar20 = param_2[1];
            bVar22 = bVar20 < (byte)pcVar19[1];
            if (bVar20 != pcVar19[1]) goto LAB_004100f0;
            param_2 = param_2 + 2;
            pcVar19 = pcVar19 + 2;
          } while (bVar20 != 0);
          uVar16 = 0;
LAB_004100f5:
          if (uVar16 != 0) {
            sprintf(local_4e0,"!Bug! Couldn\'t resolve %s-skill. Report!");
            FUN_004f6510();
            FUN_004fb870();
          }
        }
      }
    }
  }
  __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
  return;
LAB_0040fe99:
  iVar14 = feof(_File);
  if (iVar14 != 0) goto LAB_0040fea7;
  goto LAB_0040fe20;
}



/* Extracted native producer 0051b450; operand-closure */

uint __fastcall FUN_0051b450(int param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  char *pcVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  bool bVar8;
  double dVar9;
  
  pbVar5 = param_2;
  do {
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
  } while (bVar1 != 0);
  if (pbVar5 == param_2 + 1) {
    return 0;
  }
  if (DAT_0a784144 == 2) {
    return 0x50;
  }
  pcVar3 = "COMMON";
  pbVar5 = param_2;
  do {
    bVar1 = *pbVar5;
    bVar8 = bVar1 < (byte)*pcVar3;
    if (bVar1 != *pcVar3) {
LAB_0051b4b5:
      uVar2 = -(uint)bVar8 | 1;
      goto LAB_0051b4ba;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar5[1];
    bVar8 = bVar1 < (byte)pcVar3[1];
    if (bVar1 != pcVar3[1]) goto LAB_0051b4b5;
    pbVar5 = pbVar5 + 2;
    pcVar3 = pcVar3 + 2;
  } while (bVar1 != 0);
  uVar2 = 0;
LAB_0051b4ba:
  if (uVar2 == 0) {
    return 0x3c;
  }
  pcVar3 = "THROWING";
  pbVar5 = param_2;
  do {
    bVar1 = *pbVar5;
    bVar8 = bVar1 < (byte)*pcVar3;
    if (bVar1 != *pcVar3) {
LAB_0051b4f1:
      uVar2 = -(uint)bVar8 | 1;
      goto LAB_0051b4f6;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar5[1];
    bVar8 = bVar1 < (byte)pcVar3[1];
    if (bVar1 != pcVar3[1]) goto LAB_0051b4f1;
    pbVar5 = pbVar5 + 2;
    pcVar3 = pcVar3 + 2;
  } while (bVar1 != 0);
  uVar2 = 0;
LAB_0051b4f6:
  if (uVar2 == 0) {
    if (param_1 != -1) {
      dVar9 = ceil((double)(((uint)(byte)(&DAT_0615148b)[param_1 * 0x568] +
                            (uint)(byte)(&DAT_0615148d)[param_1 * 0x568] * 2) / 3));
      return (int)dVar9 << 2;
    }
    dVar9 = ceil((double)(((uint)DAT_0a72b1b5 + (uint)DAT_0a72b1ae + (uint)DAT_0a72b1aa) / 3));
    return (int)dVar9 << 2;
  }
  pcVar3 = "MOVEDODGE";
  pbVar5 = param_2;
  do {
    bVar1 = *pbVar5;
    bVar8 = bVar1 < (byte)*pcVar3;
    if (bVar1 != *pcVar3) {
LAB_0051b5d3:
      uVar2 = -(uint)bVar8 | 1;
      goto LAB_0051b5d8;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar5[1];
    bVar8 = bVar1 < (byte)pcVar3[1];
    if (bVar1 != pcVar3[1]) goto LAB_0051b5d3;
    pbVar5 = pbVar5 + 2;
    pcVar3 = pcVar3 + 2;
  } while (bVar1 != 0);
  uVar2 = 0;
LAB_0051b5d8:
  if (uVar2 == 0) {
    uVar2 = FUN_0051b400();
    return uVar2;
  }
  if (param_1 == -1) {
    iVar7 = 0;
    pbVar6 = &DAT_0a72a708;
    pbVar5 = param_2;
    pbVar4 = pbVar6;
LAB_0051b600:
    do {
      bVar1 = *pbVar6;
      bVar8 = bVar1 < *pbVar5;
      if (bVar1 == *pbVar5) {
        if (bVar1 != 0) {
          bVar1 = pbVar6[1];
          bVar8 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_0051b620;
          pbVar6 = pbVar6 + 2;
          pbVar5 = pbVar5 + 2;
          if (bVar1 != 0) goto LAB_0051b600;
        }
        uVar2 = 0;
      }
      else {
LAB_0051b620:
        uVar2 = -(uint)bVar8 | 1;
      }
      if (uVar2 == 0) {
        return (uint)(byte)(&DAT_0a72a992)[iVar7];
      }
      pbVar6 = pbVar4 + 0xc;
      iVar7 = iVar7 + 1;
      pbVar5 = param_2;
      pbVar4 = pbVar6;
      if (0xa72a95f < (int)pbVar6) {
        return 1000;
      }
    } while( true );
  }
  pcVar3 = "HIDEWORKING";
  pbVar5 = param_2;
  do {
    bVar1 = *pbVar5;
    bVar8 = bVar1 < (byte)*pcVar3;
    if (bVar1 != *pcVar3) {
LAB_0051b676:
      uVar2 = -(uint)bVar8 | 1;
      goto LAB_0051b67b;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar5[1];
    bVar8 = bVar1 < (byte)pcVar3[1];
    if (bVar1 != pcVar3[1]) goto LAB_0051b676;
    pbVar5 = pbVar5 + 2;
    pcVar3 = pcVar3 + 2;
  } while (bVar1 != 0);
  uVar2 = 0;
LAB_0051b67b:
  if (uVar2 != 0) {
    return (uint)(byte)(&DAT_06151440)[param_1 * 0x568];
  }
  pcVar3 = "TIMBERCRAFT";
  pbVar5 = param_2;
  do {
    bVar1 = *pbVar5;
    bVar8 = bVar1 < (byte)*pcVar3;
    if (bVar1 != *pcVar3) {
LAB_0051b6c0:
      uVar2 = -(uint)bVar8 | 1;
      goto LAB_0051b6c5;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar5[1];
    bVar8 = bVar1 < (byte)pcVar3[1];
    if (bVar1 != pcVar3[1]) goto LAB_0051b6c0;
    pbVar5 = pbVar5 + 2;
    pcVar3 = pcVar3 + 2;
  } while (bVar1 != 0);
  uVar2 = 0;
LAB_0051b6c5:
  if (uVar2 != 0) {
    return (uint)(byte)(&DAT_06151441)[param_1 * 0x568];
  }
  pcVar3 = "DODGE";
  pbVar5 = param_2;
  do {
    bVar1 = *pbVar5;
    bVar8 = bVar1 < (byte)*pcVar3;
    if (bVar1 != *pcVar3) {
LAB_0051b704:
      uVar2 = -(uint)bVar8 | 1;
      goto LAB_0051b709;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar5[1];
    bVar8 = bVar1 < (byte)pcVar3[1];
    if (bVar1 != pcVar3[1]) goto LAB_0051b704;
    pbVar5 = pbVar5 + 2;
    pcVar3 = pcVar3 + 2;
  } while (bVar1 != 0);
  uVar2 = 0;
LAB_0051b709:
  if (uVar2 == 0) {
    return (uint)(byte)(&DAT_061514c9)[param_1 * 0x568];
  }
  iVar7 = 0;
  param_1 = param_1 * 0x568;
  pbVar5 = &DAT_06151515 + param_1;
  pbVar4 = param_2;
  pbVar6 = pbVar5;
LAB_0051b736:
  do {
    bVar1 = *pbVar5;
    bVar8 = bVar1 < *pbVar4;
    if (bVar1 == *pbVar4) {
      if (bVar1 != 0) {
        bVar1 = pbVar5[1];
        bVar8 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_0051b756;
        pbVar5 = pbVar5 + 2;
        pbVar4 = pbVar4 + 2;
        if (bVar1 != 0) goto LAB_0051b736;
      }
      uVar2 = 0;
    }
    else {
LAB_0051b756:
      uVar2 = -(uint)bVar8 | 1;
    }
    if (uVar2 == 0) {
      return (uint)(byte)(&DAT_06151545)[iVar7 + param_1];
    }
    iVar7 = iVar7 + 1;
    pbVar5 = pbVar6 + 0xc;
    pbVar4 = param_2;
    pbVar6 = pbVar5;
    if (3 < iVar7) {
      iVar7 = param_1 - (int)param_2;
      do {
        bVar1 = *param_2;
        param_2 = param_2 + 1;
        param_2[iVar7 + 0x6151514] = bVar1;
      } while (bVar1 != 0);
      bVar1 = FUN_0040fc30();
      (&DAT_06151545)[param_1] = bVar1;
      return (uint)bVar1;
    }
  } while( true );
}



/* Extracted native producer 00526430; operand-closure */

int __fastcall PreferredWeapon(int actor,int order)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  char *pcVar6;
  byte bVar7;
  byte *pbVar8;
  int iVar9;
  bool bVar10;
  int local_14;
  int local_8;
  
  bVar7 = 0;
  iVar9 = 0;
  iVar2 = actor * 0x568;
  local_14 = -1;
  local_8 = -1;
  pbVar4 = &DAT_06151515 + iVar2;
  pbVar8 = pbVar4;
  do {
    pbVar5 = pbVar8;
    do {
      bVar1 = *pbVar5;
      pbVar5 = pbVar5 + 1;
    } while (bVar1 != 0);
    if (pbVar5 != pbVar8 + 1) {
      pcVar6 = "DAGGER";
      pbVar5 = pbVar8;
      do {
        bVar1 = *pbVar5;
        bVar10 = bVar1 < (byte)*pcVar6;
        if (bVar1 != *pcVar6) {
LAB_00526497:
          uVar3 = -(uint)bVar10 | 1;
          goto LAB_0052649c;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar5[1];
        bVar10 = bVar1 < (byte)pcVar6[1];
        if (bVar1 != pcVar6[1]) goto LAB_00526497;
        pbVar5 = pbVar5 + 2;
        pcVar6 = pcVar6 + 2;
      } while (bVar1 != 0);
      uVar3 = 0;
LAB_0052649c:
      if (uVar3 == 0) {
        *(undefined4 *)pbVar8 = DAT_0059052c;
        *(undefined2 *)(pbVar8 + 4) = DAT_00590530;
      }
      if (bVar7 < (byte)(&DAT_06151545)[iVar9 + iVar2]) {
        local_14 = iVar9;
        bVar7 = (&DAT_06151545)[iVar9 + iVar2];
      }
    }
    iVar9 = iVar9 + 1;
    pbVar8 = pbVar8 + 0xc;
  } while (iVar9 < 4);
  if (local_14 == -1) {
    return -1;
  }
  bVar7 = 0;
  iVar9 = 0;
  do {
    pbVar8 = pbVar4;
    do {
      bVar1 = *pbVar8;
      pbVar8 = pbVar8 + 1;
    } while (bVar1 != 0);
    if ((pbVar8 != pbVar4 + 1) && (iVar9 != local_14)) {
      pbVar5 = &DAT_06151515 + iVar2 + local_14 * 0xc;
      pbVar8 = pbVar4;
      do {
        bVar1 = *pbVar5;
        bVar10 = bVar1 < *pbVar8;
        if (bVar1 != *pbVar8) {
LAB_00526531:
          uVar3 = -(uint)bVar10 | 1;
          goto LAB_00526536;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar5[1];
        bVar10 = bVar1 < pbVar8[1];
        if (bVar1 != pbVar8[1]) goto LAB_00526531;
        pbVar5 = pbVar5 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar1 != 0);
      uVar3 = 0;
LAB_00526536:
      if ((uVar3 != 0) && (bVar7 < (byte)(&DAT_06151545)[iVar9 + iVar2])) {
        local_8 = iVar9;
        bVar7 = (&DAT_06151545)[iVar9 + iVar2];
      }
    }
    iVar9 = iVar9 + 1;
    pbVar4 = pbVar4 + 0xc;
    if (3 < iVar9) {
      if (order == 2) {
        local_14 = local_8;
      }
      return local_14;
    }
  } while( true );
}



/* Extracted native producer 00535490; operand-closure */

void FUN_00535490(void)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  byte *pbVar7;
  uint uVar8;
  byte *pbVar9;
  int iVar10;
  bool bVar11;
  char local_4dc [1024];
  byte local_dc [104];
  byte local_74 [108];
  uint local_8;
  
  iVar10 = DAT_0a620630;
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  iVar3 = PreferredWeapon(DAT_0a620630,0);
  iVar4 = PreferredWeapon(iVar10,2);
  if (iVar3 == -1) {
    pcVar6 = "I can hold a knife if need be but that\'s about it.";
  }
  else {
    memset(local_74,0,100);
    memset(local_dc,0,100);
    iVar10 = iVar10 * 0x568;
    pcVar5 = SkillGrade((uint)(byte)(&DAT_06151545)[iVar3 + iVar10]);
    pcVar6 = pcVar5;
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar6[(int)(local_dc + (0x67 - (int)pcVar5))] = cVar1;
    } while (cVar1 != '\0');
    pcVar6 = Lowercase(&DAT_06151515 + iVar3 * 0xc + iVar10);
    pcVar6 = Plural(pcVar6);
    sprintf(local_4dc,"I\'m %s with %s",local_74,pcVar6);
    NpcSpeech(local_4dc);
    if (iVar4 == -1) {
      pcVar6 = "but that\'s about it.";
    }
    else {
      iVar10 = DAT_0a620630 * 0x568;
      pcVar5 = SkillGrade((uint)(byte)(&DAT_06151545)[iVar4 + iVar10]);
      pcVar6 = pcVar5;
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar6[(int)(local_4dc + (0x3ff - (int)pcVar5))] = cVar1;
      } while (cVar1 != '\0');
      pbVar9 = local_dc;
      pbVar7 = local_74;
      do {
        bVar2 = *pbVar7;
        bVar11 = bVar2 < *pbVar9;
        if (bVar2 != *pbVar9) {
LAB_005355b7:
          uVar8 = -(uint)bVar11 | 1;
          goto LAB_005355bc;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar7[1];
        bVar11 = bVar2 < pbVar9[1];
        if (bVar2 != pbVar9[1]) goto LAB_005355b7;
        pbVar7 = pbVar7 + 2;
        pbVar9 = pbVar9 + 2;
      } while (bVar2 != 0);
      uVar8 = 0;
LAB_005355bc:
      if (uVar8 == 0) {
        pcVar6 = Lowercase(&DAT_06151515 + iVar4 * 0xc + iVar10);
        pcVar6 = Plural(pcVar6);
        sprintf(local_4dc,"and %s.",pcVar6);
        pcVar6 = local_4dc;
      }
      else {
        pcVar6 = Lowercase(&DAT_06151515 + iVar4 * 0xc + iVar10);
        pcVar6 = Plural(pcVar6);
        sprintf(local_4dc,"and %s with %s.",local_dc,pcVar6);
        pcVar6 = local_4dc;
      }
    }
  }
  NpcSpeech(pcVar6);
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 00535650; operand-closure */

void FUN_00535650(void)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  char *pcVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  char *pcVar11;
  char local_5ac [8];
  char acStack_5a4 [4];
  char acStack_5a0 [4];
  char local_59c [4];
  char acStack_598 [4];
  char acStack_594 [4];
  char acStack_590 [4];
  char local_58c [4];
  char acStack_588 [4];
  char acStack_584 [4];
  char acStack_580 [4];
  char local_57c [4];
  char acStack_578 [4];
  char acStack_574 [4];
  char acStack_570 [4];
  char local_56c [2];
  char local_56a;
  byte local_1ac [104];
  byte local_144 [104];
  char local_dc [8];
  char local_d4 [96];
  char local_74 [8];
  char local_6c [100];
  uint local_8;
  
  iVar9 = DAT_0a620630;
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  PreferredWeapon(DAT_0a620630,0);
  PreferredWeapon(iVar9,2);
  iVar8 = iVar9 * 0x568;
  if ((&DAT_06151401)[iVar8] == '\r') {
    iVar9 = 0;
    uVar3 = rand();
    uVar3 = uVar3 & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    do {
      uVar4 = rand();
      uVar4 = uVar4 & 0x80000001;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
      }
      iVar9 = iVar9 + 1;
      if (iVar9 == 10) {
        uVar3 = 0xffffffff;
      }
    } while (uVar4 == uVar3);
    bVar10 = (*(byte *)(&DAT_0615192c + DAT_0a620630 * 0x15a) & 2) == 0;
    switch((&DAT_06151488)[DAT_0a620630 * 0x568]) {
    case 0:
    case 2:
    case 3:
      iVar9 = 1;
      break;
    case 1:
    case 4:
    case 5:
    case 6:
      iVar9 = 2;
      break;
    case 7:
    case 8:
    case 9:
      iVar9 = 3;
      break;
    default:
      iVar9 = 0;
    }
    if (iVar9 == 1) {
      if (bVar10) {
        local_56c[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x40];
        local_56c[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x41];
        local_5ac[4] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[4];
        local_5ac[5] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[5];
        local_5ac[6] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[6];
        local_5ac[7] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[7];
        local_5ac[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0];
        local_5ac[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[1];
        local_5ac[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[2];
        local_5ac[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[3];
        acStack_5a4[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[8];
        acStack_5a4[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[9];
        acStack_5a4[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[10];
        acStack_5a4[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0xb];
        acStack_5a0[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0xc];
        acStack_5a0[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0xd];
        acStack_5a0[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0xe];
        acStack_5a0[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0xf];
        acStack_598[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x14];
        acStack_598[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x15];
        acStack_598[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x16];
        acStack_598[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x17];
        local_59c[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x10];
        local_59c[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x11];
        local_59c[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x12];
        local_59c[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x13];
        acStack_594[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x18];
        acStack_594[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x19];
        acStack_594[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x1a];
        acStack_594[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x1b];
        acStack_590[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x1c];
        acStack_590[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x1d];
        acStack_590[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x1e];
        acStack_590[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x1f];
        local_58c[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x20];
        local_58c[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x21];
        local_58c[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x22];
        local_58c[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x23];
        acStack_588[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x24];
        acStack_588[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x25];
        acStack_588[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x26];
        acStack_588[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x27];
        acStack_584[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x28];
        acStack_584[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x29];
        acStack_584[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x2a];
        acStack_584[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x2b];
        acStack_580[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x2c];
        acStack_580[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x2d];
        acStack_580[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x2e];
        acStack_580[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x2f];
        local_57c[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x30];
        local_57c[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x31];
        local_57c[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x32];
        local_57c[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x33];
        acStack_578[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x34];
        acStack_578[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x35];
        acStack_578[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x36];
        acStack_578[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x37];
        acStack_574[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x38];
        acStack_574[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x39];
        acStack_574[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x3a];
        acStack_574[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x3b];
        acStack_570[0] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x3c];
        acStack_570[1] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x3d];
        acStack_570[2] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x3e];
        acStack_570[3] = s_I_m_soothsayer_old_as_time__I_kn_005b1e58[0x3f];
      }
      else {
        pcVar6 = "Well for one, I know songs to sink nosy youngsters into a bog.";
        pcVar11 = local_5ac;
        for (iVar9 = 0xf; iVar9 != 0; iVar9 = iVar9 + -1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar11 = pcVar11 + 4;
        }
        *(undefined2 *)pcVar11 = *(undefined2 *)pcVar6;
        pcVar11[2] = pcVar6[2];
      }
    }
    else if (iVar9 == 2) {
      if (bVar10) {
        pcVar6 = 
        "Well, at least so far my powers and advises have assured welfare of the people here.";
        pcVar11 = local_5ac;
        for (iVar9 = 0x15; iVar9 != 0; iVar9 = iVar9 + -1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar11 = pcVar11 + 4;
        }
        *pcVar11 = *pcVar6;
      }
      else {
        local_56c[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x40];
        local_56c[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x41];
        local_5ac[4] = s_Curious_you_may_be__but_my_exper_005b1ea0[4];
        local_5ac[5] = s_Curious_you_may_be__but_my_exper_005b1ea0[5];
        local_5ac[6] = s_Curious_you_may_be__but_my_exper_005b1ea0[6];
        local_5ac[7] = s_Curious_you_may_be__but_my_exper_005b1ea0[7];
        local_5ac[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0];
        local_5ac[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[1];
        local_5ac[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[2];
        local_5ac[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[3];
        acStack_5a4[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[8];
        acStack_5a4[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[9];
        acStack_5a4[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[10];
        acStack_5a4[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0xb];
        acStack_5a0[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0xc];
        acStack_5a0[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0xd];
        acStack_5a0[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0xe];
        acStack_5a0[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0xf];
        local_56a = s_Curious_you_may_be__but_my_exper_005b1ea0[0x42];
        acStack_598[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x14];
        acStack_598[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x15];
        acStack_598[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x16];
        acStack_598[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x17];
        local_59c[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x10];
        local_59c[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x11];
        local_59c[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x12];
        local_59c[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x13];
        acStack_594[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x18];
        acStack_594[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x19];
        acStack_594[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x1a];
        acStack_594[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x1b];
        acStack_590[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x1c];
        acStack_590[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x1d];
        acStack_590[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x1e];
        acStack_590[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x1f];
        local_58c[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x20];
        local_58c[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x21];
        local_58c[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x22];
        local_58c[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x23];
        acStack_588[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x24];
        acStack_588[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x25];
        acStack_588[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x26];
        acStack_588[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x27];
        acStack_584[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x28];
        acStack_584[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x29];
        acStack_584[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x2a];
        acStack_584[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x2b];
        acStack_580[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x2c];
        acStack_580[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x2d];
        acStack_580[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x2e];
        acStack_580[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x2f];
        local_57c[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x30];
        local_57c[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x31];
        local_57c[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x32];
        local_57c[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x33];
        acStack_578[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x34];
        acStack_578[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x35];
        acStack_578[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x36];
        acStack_578[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x37];
        acStack_574[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x38];
        acStack_574[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x39];
        acStack_574[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x3a];
        acStack_574[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x3b];
        acStack_570[0] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x3c];
        acStack_570[1] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x3d];
        acStack_570[2] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x3e];
        acStack_570[3] = s_Curious_you_may_be__but_my_exper_005b1ea0[0x3f];
      }
    }
    else if (iVar9 == 3) {
      if (bVar10) {
        pcVar6 = "I\'m a mere negotiator between the people and the spirit world.";
        pcVar11 = local_5ac;
        for (iVar9 = 0xf; iVar9 != 0; iVar9 = iVar9 + -1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar11 = pcVar11 + 4;
        }
        *(undefined2 *)pcVar11 = *(undefined2 *)pcVar6;
        pcVar11[2] = pcVar6[2];
      }
      else {
        local_5ac[0] = s_Hehehe____005b1dc8[0];
        local_5ac[1] = s_Hehehe____005b1dc8[1];
        local_5ac[2] = s_Hehehe____005b1dc8[2];
        local_5ac[3] = s_Hehehe____005b1dc8[3];
        local_5ac[4] = s_Hehehe____005b1dc8[4];
        local_5ac[5] = s_Hehehe____005b1dc8[5];
        local_5ac[6] = s_Hehehe____005b1dc8[6];
        local_5ac[7] = s_Hehehe____005b1dc8[7];
        acStack_5a4[0] = s_Hehehe____005b1dc8[8];
        acStack_5a4[1] = s_Hehehe____005b1dc8[9];
      }
    }
    else if (bVar10) {
      local_58c[0] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x20];
      local_5ac[4] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[4];
      local_5ac[5] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[5];
      local_5ac[6] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[6];
      local_5ac[7] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[7];
      local_5ac[0] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0];
      local_5ac[1] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[1];
      local_5ac[2] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[2];
      local_5ac[3] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[3];
      acStack_5a4[0] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[8];
      acStack_5a4[1] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[9];
      acStack_5a4[2] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[10];
      acStack_5a4[3] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0xb];
      acStack_5a0[0] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0xc];
      acStack_5a0[1] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0xd];
      acStack_5a0[2] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0xe];
      acStack_5a0[3] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0xf];
      acStack_598[0] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x14];
      acStack_598[1] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x15];
      acStack_598[2] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x16];
      acStack_598[3] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x17];
      local_59c[0] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x10];
      local_59c[1] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x11];
      local_59c[2] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x12];
      local_59c[3] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x13];
      acStack_594[0] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x18];
      acStack_594[1] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x19];
      acStack_594[2] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x1a];
      acStack_594[3] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x1b];
      acStack_590[0] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x1c];
      acStack_590[1] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x1d];
      acStack_590[2] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x1e];
      acStack_590[3] = s_The_beard_doesn_t_grow_in_a_day__005b1f60[0x1f];
    }
    else {
      acStack_594[0] = s_Who_has_beard_has_the_power__005b1f40[0x18];
      acStack_594[1] = s_Who_has_beard_has_the_power__005b1f40[0x19];
      acStack_594[2] = s_Who_has_beard_has_the_power__005b1f40[0x1a];
      acStack_594[3] = s_Who_has_beard_has_the_power__005b1f40[0x1b];
      local_5ac[4] = s_Who_has_beard_has_the_power__005b1f40[4];
      local_5ac[5] = s_Who_has_beard_has_the_power__005b1f40[5];
      local_5ac[6] = s_Who_has_beard_has_the_power__005b1f40[6];
      local_5ac[7] = s_Who_has_beard_has_the_power__005b1f40[7];
      local_5ac[0] = s_Who_has_beard_has_the_power__005b1f40[0];
      local_5ac[1] = s_Who_has_beard_has_the_power__005b1f40[1];
      local_5ac[2] = s_Who_has_beard_has_the_power__005b1f40[2];
      local_5ac[3] = s_Who_has_beard_has_the_power__005b1f40[3];
      acStack_5a4[0] = s_Who_has_beard_has_the_power__005b1f40[8];
      acStack_5a4[1] = s_Who_has_beard_has_the_power__005b1f40[9];
      acStack_5a4[2] = s_Who_has_beard_has_the_power__005b1f40[10];
      acStack_5a4[3] = s_Who_has_beard_has_the_power__005b1f40[0xb];
      acStack_5a0[0] = s_Who_has_beard_has_the_power__005b1f40[0xc];
      acStack_5a0[1] = s_Who_has_beard_has_the_power__005b1f40[0xd];
      acStack_5a0[2] = s_Who_has_beard_has_the_power__005b1f40[0xe];
      acStack_5a0[3] = s_Who_has_beard_has_the_power__005b1f40[0xf];
      acStack_590[0] = s_Who_has_beard_has_the_power__005b1f40[0x1c];
      local_59c[0] = s_Who_has_beard_has_the_power__005b1f40[0x10];
      local_59c[1] = s_Who_has_beard_has_the_power__005b1f40[0x11];
      local_59c[2] = s_Who_has_beard_has_the_power__005b1f40[0x12];
      local_59c[3] = s_Who_has_beard_has_the_power__005b1f40[0x13];
      acStack_598[0] = s_Who_has_beard_has_the_power__005b1f40[0x14];
      acStack_598[1] = s_Who_has_beard_has_the_power__005b1f40[0x15];
      acStack_598[2] = s_Who_has_beard_has_the_power__005b1f40[0x16];
      acStack_598[3] = s_Who_has_beard_has_the_power__005b1f40[0x17];
    }
  }
  else {
    if ((&DAT_061514bc)[iVar9 * 0x15a] == 0x245) {
      iVar9 = FUN_004ab390();
      pcVar6 = (&PTR_s_delicious_0058efe4)[iVar9];
      pbVar5 = (byte *)SmithGrade((uint)(byte)(&DAT_06151442)[iVar8]);
      pcVar11 = "I\'m %s in what I do, and my goods are of %s quality.";
    }
    else {
      memset(local_dc,0,100);
      memset(local_144,0,100);
      memset(local_74,0,100);
      memset(local_1ac,0,100);
      pcVar11 = SkillGrade((uint)(byte)(&DAT_06151440)[iVar8]);
      pcVar6 = pcVar11;
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar6[(int)(local_1ac + (0x67 - (int)pcVar11))] = cVar1;
      } while (cVar1 != '\0');
      local_dc[0] = s_hideworking_005b1fbc[0];
      local_dc[1] = s_hideworking_005b1fbc[1];
      local_dc[2] = s_hideworking_005b1fbc[2];
      local_dc[3] = s_hideworking_005b1fbc[3];
      local_dc[4] = s_hideworking_005b1fbc[4];
      local_dc[5] = s_hideworking_005b1fbc[5];
      local_dc[6] = s_hideworking_005b1fbc[6];
      local_dc[7] = s_hideworking_005b1fbc[7];
      local_d4[0] = s_hideworking_005b1fbc[8];
      local_d4[1] = s_hideworking_005b1fbc[9];
      local_d4[2] = s_hideworking_005b1fbc[10];
      local_d4[3] = s_hideworking_005b1fbc[0xb];
      pcVar11 = SkillGrade((uint)(byte)(&DAT_06151441)[iVar8]);
      pcVar6 = pcVar11;
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar6[(int)(local_1ac + (-1 - (int)pcVar11))] = cVar1;
      } while (cVar1 != '\0');
      local_6c[0] = s_timbercraft_005b1fc8[8];
      local_6c[1] = s_timbercraft_005b1fc8[9];
      local_6c[2] = s_timbercraft_005b1fc8[10];
      local_6c[3] = s_timbercraft_005b1fc8[0xb];
      local_74[0] = s_timbercraft_005b1fc8[0];
      local_74[1] = s_timbercraft_005b1fc8[1];
      local_74[2] = s_timbercraft_005b1fc8[2];
      local_74[3] = s_timbercraft_005b1fc8[3];
      local_74[4] = s_timbercraft_005b1fc8[4];
      local_74[5] = s_timbercraft_005b1fc8[5];
      local_74[6] = s_timbercraft_005b1fc8[6];
      local_74[7] = s_timbercraft_005b1fc8[7];
      sprintf(local_5ac,"I\'m %s in %s ",local_144,local_dc);
      NpcSpeech(local_5ac);
      pbVar5 = local_1ac;
      pbVar7 = local_144;
      do {
        bVar2 = *pbVar7;
        bVar10 = bVar2 < *pbVar5;
        if (bVar2 != *pbVar5) {
LAB_00535a10:
          uVar3 = -(uint)bVar10 | 1;
          goto LAB_00535a15;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar7[1];
        bVar10 = bVar2 < pbVar5[1];
        if (bVar2 != pbVar5[1]) goto LAB_00535a10;
        pbVar7 = pbVar7 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar2 != 0);
      uVar3 = 0;
LAB_00535a15:
      pcVar6 = local_74;
      if (uVar3 == 0) {
        sprintf(local_5ac,"and %s.",pcVar6);
        goto LAB_00535a4e;
      }
      pbVar5 = local_1ac;
      pcVar11 = "and %s with %s.";
    }
    sprintf(local_5ac,pcVar11,pbVar5,pcVar6);
  }
LAB_00535a4e:
  NpcSpeech(local_5ac);
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 0055e9f0; operand-closure */

char * __fastcall SkillGrade(int rating)

{
  int iVar1;
  double dVar2;
  
  dVar2 = ceil((double)((rating + 5) / 10));
  iVar1 = (int)dVar2;
  if (rating == 0) {
    return s_unskilled_005e9f50;
  }
  if (10 < iVar1) {
    iVar1 = 10;
  }
  return s_unskilled_005e9f50 + iVar1 * 100;
}



/* Extracted native producer 0055ea60; operand-closure */

char * __fastcall SmithGrade(int rating)

{
  char *_Str;
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  double dVar6;
  
  DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  iVar3 = DAT_0a84b7a8 * 0x400;
  _Str = &DAT_0a941eb0 + iVar3;
  memset(_Str,0,0x400);
  dVar6 = ceil((double)((rating + 5) / 10));
  iVar4 = (int)dVar6;
  if (rating == 0) {
    iVar4 = 0;
  }
  else if (10 < iVar4) {
    iVar4 = 10;
  }
  pcVar5 = s_unskilled_005e9f50 + iVar4 * 100;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar5[(int)(_Str + (-1 - (int)(s_unskilled_005e9f50 + iVar4 * 100)))] = cVar1;
  } while (cVar1 != '\0');
  pcVar5 = strstr(_Str,"master");
  uVar2 = s_skilled_expert_005d79d0._8_4_;
  if ((pcVar5 != (char *)0x0) && (rating < 0x55)) {
    *(undefined8 *)_Str = s_skilled_expert_005d79d0._0_8_;
    *(undefined4 *)(&DAT_0a941eb8 + iVar3) = uVar2;
    *(undefined2 *)(&DAT_0a941ebc + iVar3) = s_skilled_expert_005d79d0._12_2_;
    (&DAT_0a941ebe)[iVar3] = s_skilled_expert_005d79d0[0xe];
  }
  return _Str;
}



/* Extracted native producer 0055ec00; operand-closure */

void FUN_0055ec00(void)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  byte *pbVar6;
  uint uVar7;
  byte *pbVar8;
  bool bVar9;
  char *pcVar10;
  byte local_dc [104];
  byte local_74 [108];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  iVar3 = DAT_0a84b7a8 * 0x400;
  memset(&DAT_0a941eb0 + iVar3,0,0x400);
  iVar4 = FUN_0048c160();
  if (iVar4 == 0) {
    FUN_004ebbc0();
  }
  iVar4 = FUN_0048c160();
  if (iVar4 == 0) {
    FUN_004ebbc0();
  }
  pcVar5 = (char *)FUN_0048e420();
  pcVar10 = pcVar5;
  do {
    cVar1 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar10[(int)(local_dc + (0x67 - (int)pcVar5))] = cVar1;
  } while (cVar1 != '\0');
  pcVar5 = (char *)FUN_0048e420();
  pcVar10 = pcVar5;
  do {
    cVar1 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar10[(int)(local_dc + (-1 - (int)pcVar5))] = cVar1;
  } while (cVar1 != '\0');
  pbVar8 = local_dc;
  pbVar6 = local_74;
  do {
    bVar2 = *pbVar6;
    bVar9 = bVar2 < *pbVar8;
    if (bVar2 != *pbVar8) {
LAB_0055ed16:
      uVar7 = -(uint)bVar9 | 1;
      goto LAB_0055ed1b;
    }
    if (bVar2 == 0) break;
    bVar2 = pbVar6[1];
    bVar9 = bVar2 < pbVar8[1];
    if (bVar2 != pbVar8[1]) goto LAB_0055ed16;
    pbVar6 = pbVar6 + 2;
    pbVar8 = pbVar8 + 2;
  } while (bVar2 != 0);
  uVar7 = 0;
LAB_0055ed1b:
  if (uVar7 == 0) {
    pbVar6 = local_74;
    pcVar10 = "here at %s";
  }
  else {
    pbVar6 = local_dc;
    pcVar10 = "at the region called %s";
  }
  sprintf(&DAT_0a941eb0 + iVar3,pcVar10,pbVar6);
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 0055ed60; operand-closure */

undefined * FUN_0055ed60(void)

{
  undefined *_Dst;
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  _Dst = &DAT_0a941eb0 + DAT_0a84b7a8 * 0x400;
  memset(_Dst,0,0x400);
  pcVar2 = (char *)FUN_0049bb30(0,0,9);
  pcVar3 = pcVar2;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar3[(int)(_Dst + (-1 - (int)pcVar2))] = cVar1;
  } while (cVar1 != '\0');
  return _Dst;
}



/* Extracted native producer 0055edd0; operand-closure */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __fastcall FUN_0055edd0(uint param_1)

{
  memset(&DAT_0a6c3e28,0,0x400);
  DAT_0a6c3e40 = s_wandering_around_with_you_005d7a28[0x18];
  DAT_0a6c3e40_1._0_1_ = s_wandering_around_with_you_005d7a28[0x19];
  DAT_0a6c3e28 = s_wandering_around_with_you_005d7a28[0];
  DAT_0a6c3e28_1._0_1_ = s_wandering_around_with_you_005d7a28[1];
  DAT_0a6c3e28_1._1_1_ = s_wandering_around_with_you_005d7a28[2];
  DAT_0a6c3e28_1._2_1_ = s_wandering_around_with_you_005d7a28[3];
  uRam0a6c3e2c._0_1_ = s_wandering_around_with_you_005d7a28[4];
  uRam0a6c3e2c._1_1_ = s_wandering_around_with_you_005d7a28[5];
  uRam0a6c3e2c._2_1_ = s_wandering_around_with_you_005d7a28[6];
  uRam0a6c3e2c._3_1_ = s_wandering_around_with_you_005d7a28[7];
  uRam0a6c3e30._0_1_ = s_wandering_around_with_you_005d7a28[8];
  uRam0a6c3e30._1_1_ = s_wandering_around_with_you_005d7a28[9];
  uRam0a6c3e30._2_1_ = s_wandering_around_with_you_005d7a28[10];
  uRam0a6c3e30._3_1_ = s_wandering_around_with_you_005d7a28[0xb];
  uRam0a6c3e34._0_1_ = s_wandering_around_with_you_005d7a28[0xc];
  uRam0a6c3e34._1_1_ = s_wandering_around_with_you_005d7a28[0xd];
  uRam0a6c3e34._2_1_ = s_wandering_around_with_you_005d7a28[0xe];
  uRam0a6c3e34._3_1_ = s_wandering_around_with_you_005d7a28[0xf];
  DAT_0a6c3e38 = s_wandering_around_with_you_005d7a28[0x10];
  DAT_0a6c3e38_1._0_1_ = s_wandering_around_with_you_005d7a28[0x11];
  DAT_0a6c3e38_1._1_1_ = s_wandering_around_with_you_005d7a28[0x12];
  DAT_0a6c3e38_1._2_1_ = s_wandering_around_with_you_005d7a28[0x13];
  DAT_0a6c3e38_1._3_1_ = s_wandering_around_with_you_005d7a28[0x14];
  DAT_0a6c3e38_1._4_1_ = s_wandering_around_with_you_005d7a28[0x15];
  DAT_0a6c3e38_1._5_1_ = s_wandering_around_with_you_005d7a28[0x16];
  DAT_0a6c3e38_1._6_1_ = s_wandering_around_with_you_005d7a28[0x17];
  if ((param_1 & 4) != 0) {
    DAT_0a6c3e28 = s_working_for_you_005d7a44[0];
    DAT_0a6c3e28_1._0_1_ = s_working_for_you_005d7a44[1];
    DAT_0a6c3e28_1._1_1_ = s_working_for_you_005d7a44[2];
    DAT_0a6c3e28_1._2_1_ = s_working_for_you_005d7a44[3];
    uRam0a6c3e2c._0_1_ = s_working_for_you_005d7a44[4];
    uRam0a6c3e2c._1_1_ = s_working_for_you_005d7a44[5];
    uRam0a6c3e2c._2_1_ = s_working_for_you_005d7a44[6];
    uRam0a6c3e2c._3_1_ = s_working_for_you_005d7a44[7];
    uRam0a6c3e30._0_1_ = s_working_for_you_005d7a44[8];
    uRam0a6c3e30._1_1_ = s_working_for_you_005d7a44[9];
    uRam0a6c3e30._2_1_ = s_working_for_you_005d7a44[10];
    uRam0a6c3e30._3_1_ = s_working_for_you_005d7a44[0xb];
    uRam0a6c3e34._0_1_ = s_working_for_you_005d7a44[0xc];
    uRam0a6c3e34._1_1_ = s_working_for_you_005d7a44[0xd];
    uRam0a6c3e34._2_1_ = s_working_for_you_005d7a44[0xe];
    uRam0a6c3e34._3_1_ = s_working_for_you_005d7a44[0xf];
  }
  if ((param_1 & 2) != 0) {
    DAT_0a6c3e38_1 = SUB87(s_wandering_around_with_you_005d7a28._16_8_,1);
    DAT_0a6c3e38 = s_hunting_with_you_005d7a54[0x10];
    DAT_0a6c3e28 = s_hunting_with_you_005d7a54[0];
    DAT_0a6c3e28_1._0_1_ = s_hunting_with_you_005d7a54[1];
    DAT_0a6c3e28_1._1_1_ = s_hunting_with_you_005d7a54[2];
    DAT_0a6c3e28_1._2_1_ = s_hunting_with_you_005d7a54[3];
    uRam0a6c3e2c._0_1_ = s_hunting_with_you_005d7a54[4];
    uRam0a6c3e2c._1_1_ = s_hunting_with_you_005d7a54[5];
    uRam0a6c3e2c._2_1_ = s_hunting_with_you_005d7a54[6];
    uRam0a6c3e2c._3_1_ = s_hunting_with_you_005d7a54[7];
    uRam0a6c3e30._0_1_ = s_hunting_with_you_005d7a54[8];
    uRam0a6c3e30._1_1_ = s_hunting_with_you_005d7a54[9];
    uRam0a6c3e30._2_1_ = s_hunting_with_you_005d7a54[10];
    uRam0a6c3e30._3_1_ = s_hunting_with_you_005d7a54[0xb];
    uRam0a6c3e34._0_1_ = s_hunting_with_you_005d7a54[0xc];
    uRam0a6c3e34._1_1_ = s_hunting_with_you_005d7a54[0xd];
    uRam0a6c3e34._2_1_ = s_hunting_with_you_005d7a54[0xe];
    uRam0a6c3e34._3_1_ = s_hunting_with_you_005d7a54[0xf];
  }
  if ((param_1 & 8) != 0) {
    DAT_0a6c3e58 = s_exploring_the_wilderness_and_adv_005d7a68[0x30];
    DAT_0a6c3e58_1 = s_exploring_the_wilderness_and_adv_005d7a68[0x31];
    DAT_0a6c3e28 = s_exploring_the_wilderness_and_adv_005d7a68[0];
    DAT_0a6c3e28_1._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[1];
    DAT_0a6c3e28_1._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[2];
    DAT_0a6c3e28_1._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[3];
    uRam0a6c3e2c._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[4];
    uRam0a6c3e2c._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[5];
    uRam0a6c3e2c._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[6];
    uRam0a6c3e2c._3_1_ = s_exploring_the_wilderness_and_adv_005d7a68[7];
    uRam0a6c3e30._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[8];
    uRam0a6c3e30._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[9];
    uRam0a6c3e30._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[10];
    uRam0a6c3e30._3_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0xb];
    uRam0a6c3e34._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0xc];
    uRam0a6c3e34._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0xd];
    uRam0a6c3e34._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0xe];
    uRam0a6c3e34._3_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0xf];
    DAT_0a6c3e38_1._3_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x14];
    DAT_0a6c3e38_1._4_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x15];
    DAT_0a6c3e38_1._5_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x16];
    DAT_0a6c3e38_1._6_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x17];
    DAT_0a6c3e38 = s_exploring_the_wilderness_and_adv_005d7a68[0x10];
    DAT_0a6c3e38_1._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x11];
    DAT_0a6c3e38_1._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x12];
    DAT_0a6c3e38_1._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x13];
    DAT_0a6c3e40 = s_exploring_the_wilderness_and_adv_005d7a68[0x18];
    DAT_0a6c3e40_1._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x19];
    DAT_0a6c3e40_1._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x1a];
    DAT_0a6c3e40_1._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x1b];
    uRam0a6c3e44._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x1c];
    uRam0a6c3e44._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x1d];
    uRam0a6c3e44._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x1e];
    uRam0a6c3e44._3_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x1f];
    DAT_0a6c3e48 = s_exploring_the_wilderness_and_adv_005d7a68[0x20];
    DAT_0a6c3e48_1._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x21];
    DAT_0a6c3e48_1._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x22];
    DAT_0a6c3e48_1._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x23];
    uRam0a6c3e4c._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x24];
    uRam0a6c3e4c._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x25];
    uRam0a6c3e4c._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x26];
    uRam0a6c3e4c._3_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x27];
    uRam0a6c3e50._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x28];
    uRam0a6c3e50._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x29];
    uRam0a6c3e50._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x2a];
    uRam0a6c3e50._3_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x2b];
    uRam0a6c3e54._0_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x2c];
    uRam0a6c3e54._1_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x2d];
    uRam0a6c3e54._2_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x2e];
    uRam0a6c3e54._3_1_ = s_exploring_the_wilderness_and_adv_005d7a68[0x2f];
  }
  return &DAT_0a6c3e28;
}



/* Extracted native producer 00562100; operand-closure */

void FUN_00562100(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  undefined2 *puVar11;
  char *pcVar12;
  char acStackY_c8a [74];
  undefined4 uStackY_c40;
  char local_c08 [1023];
  undefined1 auStack_809 [2];
  undefined1 auStack_807 [1023];
  char local_408 [1024];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  bVar2 = false;
  DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  iVar3 = DAT_0a84b7a8 * 0x400;
  memset(&DAT_0a941eb0 + iVar3,0,0x400);
  uStackY_c40 = 0x56215e;
  memset(&DAT_065bb650,0,0x400);
  DAT_0a625314 = 0;
  iVar8 = -0xa625318;
  pcVar5 = &DAT_0a625318;
  do {
    pcVar10 = pcVar5 + 0x82;
    DAT_0a625314 = DAT_0a625314 + 1;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      (local_408 + iVar8 + -1)[(int)pcVar5] = cVar1;
    } while (cVar1 != '\0');
    pcVar5 = local_408;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    if (pcVar5 == local_408 + 1) {
      bVar2 = true;
    }
    pcVar5 = pcVar10;
    if (local_408[0] == '<') {
      memset(local_408,0,0x400);
    }
    else {
      do {
        cVar1 = *pcVar5;
        local_c08[(int)(pcVar5 + iVar8 + -0x82)] = cVar1;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      iVar4 = 0;
      do {
        cVar1 = local_408[iVar4];
        auStack_809[iVar4 + 1] = cVar1;
        iVar4 = iVar4 + 1;
      } while (cVar1 != '\0');
      if (local_c08[0] != '.') {
        pcVar5 = local_c08;
        do {
          cVar1 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        if (pcVar5 != local_c08 + 1) {
          puVar11 = (undefined2 *)auStack_809;
          do {
            pcVar5 = (char *)((int)puVar11 + 1);
            puVar11 = (undefined2 *)((int)puVar11 + 1);
          } while (*pcVar5 != '\0');
          *puVar11 = DAT_0058c8c0;
        }
      }
      pcVar5 = &DAT_0a941eb0 + iVar3;
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      pcVar7 = auStack_809 + 1;
      do {
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      if ((char *)0x3ff <
          pcVar5 + (int)(pcVar7 + (-(int)auStack_807 - (int)(&DAT_0a941eb1 + iVar3)))) {
        __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
        return;
      }
      pcVar5 = auStack_809 + 1;
      pcVar7 = pcVar5;
      do {
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      pcVar12 = &DAT_0a941eaf + iVar3;
      do {
        pcVar9 = pcVar12 + 1;
        pcVar12 = pcVar12 + 1;
      } while (*pcVar9 != '\0');
      pcVar9 = pcVar5;
      for (uVar6 = (uint)((int)pcVar7 - (int)pcVar5) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar6 = (int)pcVar7 - (int)pcVar5 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar12 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar12 = pcVar12 + 1;
      }
    }
    iVar8 = iVar8 + -0x82;
    pcVar5 = pcVar10;
    if (bVar2) {
      __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
      return;
    }
  } while( true );
}



/* Extracted native producer 00562300; operand-closure */

void __fastcall FUN_00562300(int param_1,char *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  undefined2 *puVar11;
  char local_6c [100];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  uVar9 = 0;
  if (param_1 != 0) {
    FUN_005620c0();
  }
  iVar4 = DAT_0a625314;
  if ((*param_2 == ' ') && (param_2[1] != ' ')) {
    iVar5 = DAT_0a625314 * 0x82;
    iVar4 = DAT_0a625314 + 1;
    uVar9 = 1;
    DAT_0a625314 = iVar4;
    *(undefined2 *)(&DAT_0a625318 + iVar5) = 0x20;
  }
  uVar3 = DAT_00594170;
  uVar2 = DAT_0059416c;
  pcVar7 = param_2;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  if (pcVar7 == param_2 + 1) {
    iVar5 = iVar4 * 0x82;
    iVar4 = iVar4 + 1;
    *(undefined4 *)(&DAT_0a625318 + iVar5) = DAT_0059416c;
    (&DAT_0a62531c)[iVar5] = uVar3;
    *(undefined4 *)(&DAT_0a625318 + iVar4 * 0x82) = uVar2;
    (&DAT_0a62531c)[iVar4 * 0x82] = uVar3;
  }
  else {
    pcVar7 = param_2;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    if (uVar9 < (uint)((int)pcVar7 - (int)(param_2 + 1))) {
      do {
        sprintf(local_6c,"%c",(uint)(byte)param_2[uVar9]);
        iVar4 = DAT_0a625314;
        cVar1 = param_2[uVar9];
        if (cVar1 == ' ') {
          if (param_2[uVar9 + 1] == ' ') {
            pcVar7 = local_6c;
            do {
              cVar1 = *pcVar7;
              pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            uVar8 = (int)pcVar7 - (int)local_6c;
            pcVar7 = (char *)((int)&DAT_0a625314 + DAT_0a625314 * 0x82 + 3);
            do {
              pcVar10 = pcVar7 + 1;
              pcVar7 = pcVar7 + 1;
            } while (*pcVar10 != '\0');
LAB_005624c8:
            pcVar10 = local_6c;
            for (uVar6 = uVar8 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar7 = *(undefined4 *)pcVar10;
              pcVar10 = pcVar10 + 4;
              pcVar7 = pcVar7 + 4;
            }
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *pcVar7 = *pcVar10;
              pcVar10 = pcVar10 + 1;
              pcVar7 = pcVar7 + 1;
            }
          }
          else {
            iVar4 = DAT_0a625314 + 1;
            DAT_0a625314 = iVar4;
          }
        }
        else if (cVar1 == '<') {
          pcVar7 = &DAT_0a625318 + DAT_0a625314 * 0x82;
          do {
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          if (pcVar7 != &DAT_0a625319 + DAT_0a625314 * 0x82) {
            DAT_0a625314 = DAT_0a625314 + 1;
          }
          iVar4 = DAT_0a625314;
          puVar11 = (undefined2 *)((int)&DAT_0a625314 + DAT_0a625314 * 0x82 + 3);
          do {
            pcVar7 = (char *)((int)puVar11 + 1);
            puVar11 = (undefined2 *)((int)puVar11 + 1);
          } while (*pcVar7 != '\0');
          *puVar11 = DAT_005b3390;
        }
        else {
          if (cVar1 != '>') {
            pcVar7 = local_6c;
            do {
              cVar1 = *pcVar7;
              pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            uVar8 = (int)pcVar7 - (int)local_6c;
            pcVar7 = (char *)((int)&DAT_0a625314 + DAT_0a625314 * 0x82 + 3);
            do {
              pcVar10 = pcVar7 + 1;
              pcVar7 = pcVar7 + 1;
            } while (*pcVar10 != '\0');
            goto LAB_005624c8;
          }
          puVar11 = (undefined2 *)((int)&DAT_0a625314 + DAT_0a625314 * 0x82 + 3);
          do {
            pcVar7 = (char *)((int)puVar11 + 1);
            puVar11 = (undefined2 *)((int)puVar11 + 1);
          } while (*pcVar7 != '\0');
          iVar4 = DAT_0a625314 + 1;
          *puVar11 = DAT_005d81c0;
          DAT_0a625314 = iVar4;
        }
        uVar9 = uVar9 + 1;
        pcVar7 = param_2;
        do {
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
      } while (uVar9 < (uint)((int)pcVar7 - (int)(param_2 + 1)));
    }
    pcVar7 = &DAT_0a625318 + iVar4 * 0x82;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    if (pcVar7 == &DAT_0a625319 + iVar4 * 0x82) goto LAB_00562511;
  }
  DAT_0a625314 = iVar4 + 1;
LAB_00562511:
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 00419810; extra-producers */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00419810(int param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  char local_74 [108];
  uint local_8;
  
  uVar1 = _DAT_00624fb0;
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  _DAT_00624fa8 = s_some_day_005912e8._0_8_;
  _DAT_00624fb0 = CONCAT31(DAT_00624fb0_1,s_some_day_005912e8[8]);
  if (param_1 < 0xf) {
    _DAT_00624fa8 = CONCAT44(s_shortly_005912f4._4_4_,s_shortly_005912f4._0_4_);
    __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
    return;
  }
  if (param_1 < 0x28) {
    _DAT_00624fa8 = CONCAT44(s_in_half_an_hour_005912fc._4_4_,s_in_half_an_hour_005912fc._0_4_);
    _DAT_00624fb0 = s_in_half_an_hour_005912fc._8_4_;
    _DAT_00624fb4 = s_in_half_an_hour_005912fc._12_4_;
    __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
    return;
  }
  if (param_1 < 0x46) {
    DAT_00624fb0_1._2_1_ = SUB41(uVar1,3);
    _DAT_00624fb0 = CONCAT12(s_in_an_hour_0059130c[10],s_in_an_hour_0059130c._8_2_);
    _DAT_00624fa8 = s_in_an_hour_0059130c._0_8_;
    __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
    return;
  }
  if (param_1 < 0x79) {
    pcVar2 = "in a few hours";
  }
  else {
    if (param_1 < 0x515) {
      FUN_0055f8e0();
      pcVar2 = _strlwr(local_74);
      sprintf(&DAT_00624fa8,"by %s",pcVar2);
      __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
      return;
    }
    if (1 < param_1 / 0x5a0) {
      uVar1 = FUN_0055eb50();
      sprintf(&DAT_00624fa8,"after %s",uVar1);
      __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
      return;
    }
    pcVar2 = "tomorrow";
  }
  sprintf(&DAT_00624fa8,pcVar2);
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 004aaba0; extra-producers */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __fastcall FUN_004aaba0(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  
  iVar5 = DAT_0a620630;
  iVar7 = DAT_0a620630 * 0x568;
  if ((*(uint *)(&DAT_061516ec + iVar7) & 0x40000) != 0) {
    _DAT_0a622860 = CONCAT62(DAT_0a622860_1._1_6_,s_I_don_t_think_so__005a006c._16_2_);
    DAT_0a622850 = s_I_don_t_think_so__005a006c._0_4_;
    _DAT_0a622854 = s_I_don_t_think_so__005a006c._4_4_;
    uRam0a622858 = s_I_don_t_think_so__005a006c._8_4_;
    uRam0a62285c = s_I_don_t_think_so__005a006c._12_4_;
    return false;
  }
  if (((&DAT_06151634)[iVar7] & 0x40) != 0) {
    pcVar3 = "That doesn\'t suit me. I have things of my own to take care of.";
    puVar8 = &DAT_0a622850;
    for (iVar5 = 0xf; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      puVar8 = puVar8 + 1;
    }
    *(undefined2 *)puVar8 = *(undefined2 *)pcVar3;
    *(char *)((int)puVar8 + 2) = pcVar3[2];
    return false;
  }
  if ((&DAT_0615190c)[DAT_0a620630 * 0x15a] != 0) {
    _DAT_0a622870 = s_Not_now__but_maybe_in_the_future_005a00c0._32_2_;
    DAT_0a622850 = s_Not_now__but_maybe_in_the_future_005a00c0._0_4_;
    _DAT_0a622854 = s_Not_now__but_maybe_in_the_future_005a00c0._4_4_;
    uRam0a622858 = s_Not_now__but_maybe_in_the_future_005a00c0._8_4_;
    uRam0a62285c = s_Not_now__but_maybe_in_the_future_005a00c0._12_4_;
    _DAT_0a622860 =
         CONCAT44(s_Not_now__but_maybe_in_the_future_005a00c0._20_4_,
                  s_Not_now__but_maybe_in_the_future_005a00c0._16_4_);
    uRam0a622868 = s_Not_now__but_maybe_in_the_future_005a00c0._24_4_;
    uRam0a62286c = s_Not_now__but_maybe_in_the_future_005a00c0._28_4_;
    return false;
  }
  iVar2 = FUN_004aaac0();
  if ((iVar2 != 0) && (iVar2 = FUN_004aab50(), iVar2 != -1000)) {
    pcVar3 = NpcDisplayName(iVar2,8);
    sprintf((char *)&DAT_0a622850,
            "I don\'t think you\'ll find a companion here until our %s gets payed.",pcVar3);
    return false;
  }
  DAT_0a622850._0_1_ = s_No__I_m_not_interested__005a012c[0];
  DAT_0a622850._1_1_ = s_No__I_m_not_interested__005a012c[1];
  DAT_0a622850._2_1_ = s_No__I_m_not_interested__005a012c[2];
  DAT_0a622850._3_1_ = s_No__I_m_not_interested__005a012c[3];
  DAT_0a622854._0_1_ = s_No__I_m_not_interested__005a012c[4];
  DAT_0a622854._1_1_ = s_No__I_m_not_interested__005a012c[5];
  DAT_0a622856 = s_No__I_m_not_interested__005a012c[6];
  DAT_0a622854_1._2_1_ = s_No__I_m_not_interested__005a012c[7];
  uRam0a622858._0_1_ = s_No__I_m_not_interested__005a012c[8];
  uRam0a622858._1_1_ = s_No__I_m_not_interested__005a012c[9];
  uRam0a622858._2_1_ = s_No__I_m_not_interested__005a012c[10];
  uRam0a622858._3_1_ = s_No__I_m_not_interested__005a012c[0xb];
  uRam0a62285c._0_1_ = s_No__I_m_not_interested__005a012c[0xc];
  uRam0a62285c._1_1_ = s_No__I_m_not_interested__005a012c[0xd];
  uRam0a62285c._2_1_ = s_No__I_m_not_interested__005a012c[0xe];
  uRam0a62285c._3_1_ = s_No__I_m_not_interested__005a012c[0xf];
  DAT_0a622860 = s_No__I_m_not_interested__005a012c[0x10];
  DAT_0a622860_1._0_1_ = s_No__I_m_not_interested__005a012c[0x11];
  DAT_0a622860_1._1_1_ = s_No__I_m_not_interested__005a012c[0x12];
  DAT_0a622860_1._2_1_ = s_No__I_m_not_interested__005a012c[0x13];
  DAT_0a622860_1._3_1_ = s_No__I_m_not_interested__005a012c[0x14];
  DAT_0a622860_1._4_1_ = s_No__I_m_not_interested__005a012c[0x15];
  DAT_0a622860_1._5_1_ = s_No__I_m_not_interested__005a012c[0x16];
  DAT_0a622860_1._6_1_ = s_No__I_m_not_interested__005a012c[0x17];
  if ((*(uint *)(&DAT_061516ec + iVar7) & 0x40000000) != 0) {
    DAT_0a622870 = s_Not_now__but_maybe_in_the_future_005a00c0[0x20];
    DAT_0a622870_1 = s_Not_now__but_maybe_in_the_future_005a00c0[0x21];
    DAT_0a622850._0_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0];
    DAT_0a622850._1_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[1];
    DAT_0a622850._2_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[2];
    DAT_0a622850._3_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[3];
    DAT_0a622854._0_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[4];
    DAT_0a622854._1_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[5];
    DAT_0a622856 = s_Not_now__but_maybe_in_the_future_005a00c0[6];
    DAT_0a622854_1._2_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[7];
    uRam0a622858._0_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[8];
    uRam0a622858._1_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[9];
    uRam0a622858._2_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[10];
    uRam0a622858._3_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0xb];
    uRam0a62285c._0_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0xc];
    uRam0a62285c._1_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0xd];
    uRam0a62285c._2_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0xe];
    uRam0a62285c._3_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0xf];
    DAT_0a622860_1._3_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x14];
    DAT_0a622860_1._4_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x15];
    DAT_0a622860_1._5_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x16];
    DAT_0a622860_1._6_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x17];
    DAT_0a622860 = s_Not_now__but_maybe_in_the_future_005a00c0[0x10];
    DAT_0a622860_1._0_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x11];
    DAT_0a622860_1._1_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x12];
    DAT_0a622860_1._2_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x13];
    uRam0a622868._0_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x18];
    uRam0a622868._1_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x19];
    uRam0a622868._2_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x1a];
    uRam0a622868._3_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x1b];
    uRam0a62286c._0_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x1c];
    uRam0a62286c._1_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x1d];
    uRam0a62286c._2_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x1e];
    uRam0a62286c._3_1_ = s_Not_now__but_maybe_in_the_future_005a00c0[0x1f];
    iVar4 = FUN_004aaac0();
    iVar2 = DAT_0a72b1c4;
    if (iVar4 == 0) {
      return false;
    }
    if (*(int *)(&DAT_06151480 + iVar7) == 0) {
      if (param_2 < 0x1e) {
        *(int *)(&DAT_06151480 + iVar7) = DAT_0a72b1c4 - param_2;
      }
      else {
        *(undefined4 *)(&DAT_06151480 + iVar7) = 1;
      }
    }
    uVar6 = iVar2 - *(int *)(&DAT_06151480 + iVar7) >> 0x1f;
    if ((int)((iVar2 - *(int *)(&DAT_06151480 + iVar7) ^ uVar6) - uVar6) <
        (int)((uint)(byte)(&DAT_0615148b)[iVar7] * 0xf)) {
      return false;
    }
  }
  iVar2 = FUN_004aa320();
  if (iVar2 != 0) {
    DAT_0a622850._0_1_ = s_I_really_can_t_leave_from_here__005a0144[0];
    DAT_0a622850._1_1_ = s_I_really_can_t_leave_from_here__005a0144[1];
    DAT_0a622850._2_1_ = s_I_really_can_t_leave_from_here__005a0144[2];
    DAT_0a622850._3_1_ = s_I_really_can_t_leave_from_here__005a0144[3];
    DAT_0a622854._0_1_ = s_I_really_can_t_leave_from_here__005a0144[4];
    DAT_0a622854._1_1_ = s_I_really_can_t_leave_from_here__005a0144[5];
    DAT_0a622856 = s_I_really_can_t_leave_from_here__005a0144[6];
    DAT_0a622854_1._2_1_ = s_I_really_can_t_leave_from_here__005a0144[7];
    uRam0a622858._0_1_ = s_I_really_can_t_leave_from_here__005a0144[8];
    uRam0a622858._1_1_ = s_I_really_can_t_leave_from_here__005a0144[9];
    uRam0a622858._2_1_ = s_I_really_can_t_leave_from_here__005a0144[10];
    uRam0a622858._3_1_ = s_I_really_can_t_leave_from_here__005a0144[0xb];
    uRam0a62285c._0_1_ = s_I_really_can_t_leave_from_here__005a0144[0xc];
    uRam0a62285c._1_1_ = s_I_really_can_t_leave_from_here__005a0144[0xd];
    uRam0a62285c._2_1_ = s_I_really_can_t_leave_from_here__005a0144[0xe];
    uRam0a62285c._3_1_ = s_I_really_can_t_leave_from_here__005a0144[0xf];
    _DAT_0a622860 =
         CONCAT44(s_I_really_can_t_leave_from_here__005a0144._20_4_,
                  s_I_really_can_t_leave_from_here__005a0144._16_4_);
    uRam0a622868._0_1_ = s_I_really_can_t_leave_from_here__005a0144[0x18];
    uRam0a622868._1_1_ = s_I_really_can_t_leave_from_here__005a0144[0x19];
    uRam0a622868._2_1_ = s_I_really_can_t_leave_from_here__005a0144[0x1a];
    uRam0a622868._3_1_ = s_I_really_can_t_leave_from_here__005a0144[0x1b];
    uRam0a62286c._0_1_ = s_I_really_can_t_leave_from_here__005a0144[0x1c];
    uRam0a62286c._1_1_ = s_I_really_can_t_leave_from_here__005a0144[0x1d];
    uRam0a62286c._2_1_ = s_I_really_can_t_leave_from_here__005a0144[0x1e];
    uRam0a62286c._3_1_ = s_I_really_can_t_leave_from_here__005a0144[0x1f];
    return false;
  }
  cVar1 = (&DAT_06151401)[iVar7];
  if ((((cVar1 != '\x05') && (cVar1 != '\r')) && ((&DAT_061514bc)[iVar5 * 0x15a] != 0x245)) &&
     (((cVar1 != '\x0f' && (cVar1 != '\x0e')) && (1 < (byte)(&DAT_06151466)[iVar7])))) {
    iVar5 = FUN_004aa190();
    return iVar5 == -1000;
  }
  return false;
}



/* Extracted native producer 0049b040; extra-producers */

void __fastcall FUN_0049b040(uint param_1,uint param_2,uint param_3)

{
  char *destination;
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  uint extraout_ECX;
  uint uVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  int iVar13;
  char *pcVar14;
  undefined2 *puVar15;
  int local_c28;
  int local_c24;
  int *local_c1c;
  int local_c14;
  char local_c10 [8];
  char local_c08 [4];
  char local_c04 [1012];
  undefined4 local_810 [255];
  char cStack_411;
  char local_410 [8];
  char local_408 [1020];
  uint local_c;
  
  local_c = DAT_005e200c ^ (uint)&stack0xfffffffc;
  DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  iVar2 = DAT_0a84b7a8 * 0x400;
  destination = &DAT_0a941eb0 + iVar2;
  memset(destination,0,0x400);
  if ((param_1 < 0xc00) && (param_2 < 0x800)) {
    cVar1 = (&DAT_02182200)[((int)param_1 >> 5) + ((int)param_2 >> 5) * 0x60];
  }
  else {
    cVar1 = '\0';
  }
  iVar12 = -1000;
  local_c14 = -1000;
  local_c24 = -1000;
  local_c28 = -1000;
  memset(local_810,0,0x400);
  memset(local_c10,0,0x400);
  memset(local_410,0,0x400);
  if (((cVar1 != '\n') && (cVar1 != '\f')) && (cVar1 != '\r')) {
    if ((param_3 & 1) == 0) {
      memset(local_810,0,0x400);
    }
    else {
      local_810[0] = 0x206e69;
    }
    pcVar3 = (char *)FUN_0049ad00(0xfffffc18);
    pcVar7 = pcVar3;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar7[(int)&local_c14 + (3 - (int)pcVar3)] = cVar1;
    } while (cVar1 != '\0');
    sprintf(destination,"%s%s",local_810,local_c10);
    if ((param_3 & 4) != 0) {
      *destination = '\0';
      __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
      return;
    }
    goto LAB_0049b67a;
  }
  local_c08[0] = s_no_man_s_land_0059daf8[8];
  local_c08[1] = s_no_man_s_land_0059daf8[9];
  local_c08[2] = s_no_man_s_land_0059daf8[10];
  local_c08[3] = s_no_man_s_land_0059daf8[0xb];
  local_c10[0] = s_no_man_s_land_0059daf8[0];
  local_c10[1] = s_no_man_s_land_0059daf8[1];
  local_c10[2] = s_no_man_s_land_0059daf8[2];
  local_c10[3] = s_no_man_s_land_0059daf8[3];
  local_c10[4] = s_no_man_s_land_0059daf8[4];
  local_c10[5] = s_no_man_s_land_0059daf8[5];
  local_c10[6] = s_no_man_s_land_0059daf8[6];
  local_c10[7] = s_no_man_s_land_0059daf8[7];
  local_c04[0] = s_no_man_s_land_0059daf8[0xc];
  local_c04[1] = s_no_man_s_land_0059daf8[0xd];
  iVar4 = FUN_0049acc0();
  if (iVar4 != -1000) {
    uVar5 = FUN_0049ad00(iVar4);
    sprintf(local_410,"near %s",uVar5);
    if ((param_3 & 1) == 0) {
      memset(local_810,0,0x400);
    }
    else {
      local_810[0] = 0x206e6f;
    }
    sprintf(destination,"%s%s",local_810,local_c10);
    if ((param_3 & 2) == 0) {
      puVar15 = (undefined2 *)(&DAT_0a941eaf + iVar2);
      do {
        pcVar7 = (char *)((int)puVar15 + 1);
        puVar15 = (undefined2 *)((int)puVar15 + 1);
      } while (*pcVar7 != '\0');
      *puVar15 = DAT_0058c8c0;
      pcVar7 = local_410;
      do {
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      uVar8 = (int)pcVar7 - (int)local_410;
      pcVar7 = &DAT_0a941eaf + iVar2;
      do {
        pcVar3 = pcVar7 + 1;
        pcVar7 = pcVar7 + 1;
      } while (*pcVar3 != '\0');
      pcVar3 = local_410;
      for (uVar6 = uVar8 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar7 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        pcVar7 = pcVar7 + 1;
      }
    }
    if ((param_3 & 4) != 0) {
      pcVar7 = local_410;
      do {
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar7[(int)(destination + (-1 - (int)local_410))] = cVar1;
      } while (cVar1 != '\0');
      __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
      return;
    }
    goto LAB_0049b67a;
  }
  iVar4 = 0;
  local_c1c = &DAT_02d868a0;
  uVar8 = extraout_ECX;
  do {
    if (((iVar4 != 10) && (iVar4 != 0xc)) && (iVar4 != 0xd)) {
      if (iVar12 == -1000) {
        local_c24 = 0xc00;
        local_c28 = 0x800;
        local_c14 = iVar4;
      }
      uVar6 = (int)(*local_c1c - uVar8) >> 0x1f;
      iVar13 = (*local_c1c - uVar8 ^ uVar6) - uVar6;
      uVar8 = (int)(local_c1c[-2] - param_1) >> 0x1f;
      iVar12 = (local_c1c[-2] - param_1 ^ uVar8) - uVar8;
      if (iVar12 < iVar13) {
        iVar13 = iVar12;
      }
      if ((local_c1c[-2] <= (int)param_1) && ((int)param_1 <= *local_c1c)) {
        iVar13 = 0;
      }
      uVar8 = local_c1c[1] - param_2;
      uVar9 = (int)uVar8 >> 0x1f;
      uVar6 = local_c1c[-1] - param_2;
      iVar10 = (uVar8 ^ uVar9) - uVar9;
      uVar8 = (int)uVar6 >> 0x1f;
      iVar12 = (uVar6 ^ uVar8) - uVar8;
      if (iVar12 < iVar10) {
        iVar10 = iVar12;
      }
      if ((local_c1c[-1] <= (int)param_2) && ((int)param_2 <= local_c1c[1])) {
        iVar10 = 0;
      }
      uVar8 = param_1;
      iVar12 = local_c24;
      if ((iVar10 + iVar13) / 2 < (local_c24 + local_c28) / 2) {
        iVar12 = iVar13;
        local_c28 = iVar10;
        local_c24 = iVar13;
        local_c14 = iVar4;
      }
    }
    local_c1c = local_c1c + 10;
    iVar4 = iVar4 + 1;
  } while ((int)local_c1c < 0x2d86ad0);
  if (local_c14 == -1000) {
    if ((param_3 & 1) == 0) {
      memset(local_810,0,0x400);
    }
    else {
      local_810[0] = 0x206e6f;
    }
    sprintf(destination,"%s%s",local_810,local_c10);
    goto LAB_0049b67a;
  }
  if ((int)uVar8 < (int)(&DAT_02d86898)[local_c14 * 10]) {
    if ((int)(&DAT_02d868a0)[local_c14 * 10] < (int)uVar8) goto LAB_0049b4ce;
    pcVar7 = &cStack_411;
    do {
      pcVar3 = pcVar7;
      pcVar7 = pcVar3 + 1;
    } while (pcVar3[1] != '\0');
    *(undefined4 *)pcVar7 = s_west_of_0059db34._0_4_;
    *(undefined4 *)(pcVar3 + 5) = s_west_of_0059db34._4_4_;
    cVar1 = s_west_of_0059db34[8];
LAB_0049b51e:
    pcVar7[8] = cVar1;
  }
  else {
    if ((int)(&DAT_02d868a0)[local_c14 * 10] < (int)uVar8) {
LAB_0049b4ce:
      pcVar7 = &cStack_411;
      do {
        pcVar3 = pcVar7;
        pcVar7 = pcVar3 + 1;
      } while (pcVar3[1] != '\0');
      *(undefined4 *)pcVar7 = s_east_of_0059db28._0_4_;
      *(undefined4 *)(pcVar3 + 5) = s_east_of_0059db28._4_4_;
      cVar1 = s_east_of_0059db28[8];
      goto LAB_0049b51e;
    }
    pcVar7 = &cStack_411;
    if ((int)param_2 < (int)(&DAT_02d8689c)[local_c14 * 10]) {
      do {
        pcVar3 = pcVar7;
        pcVar7 = pcVar3 + 1;
      } while (pcVar3[1] != '\0');
      *(undefined4 *)(pcVar3 + 1) = s_north_of_0059db10._0_4_;
      *(undefined4 *)(pcVar3 + 5) = s_north_of_0059db10._4_4_;
      *(undefined2 *)(pcVar3 + 9) = s_north_of_0059db10._8_2_;
    }
    else {
      do {
        pcVar3 = pcVar7;
        pcVar7 = pcVar3 + 1;
      } while (pcVar3[1] != '\0');
      *(undefined4 *)(pcVar3 + 1) = s_south_of_0059db1c._0_4_;
      *(undefined4 *)(pcVar3 + 5) = s_south_of_0059db1c._4_4_;
      *(undefined2 *)(pcVar3 + 9) = s_south_of_0059db1c._8_2_;
    }
  }
  pcVar7 = (&PTR_s_Kaumo_0058e3c4)[local_c14];
  pcVar3 = pcVar7;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar14 = &cStack_411;
  do {
    pcVar11 = pcVar14 + 1;
    pcVar14 = pcVar14 + 1;
  } while (*pcVar11 != '\0');
  pcVar11 = pcVar7;
  for (uVar8 = (uint)((int)pcVar3 - (int)pcVar7) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar8 = (int)pcVar3 - (int)pcVar7 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar14 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar14 = pcVar14 + 1;
  }
  if ((param_3 & 1) == 0) {
    memset(local_810,0,0x400);
  }
  else {
    local_810[0] = 0x206e6f;
  }
  sprintf(destination,"%s%s",local_810,local_c10);
  if ((param_3 & 2) == 0) {
    puVar15 = (undefined2 *)(&DAT_0a941eaf + iVar2);
    do {
      pcVar7 = (char *)((int)puVar15 + 1);
      puVar15 = (undefined2 *)((int)puVar15 + 1);
    } while (*pcVar7 != '\0');
    *puVar15 = DAT_0058c8c0;
    pcVar7 = local_410;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    uVar8 = (int)pcVar7 - (int)local_410;
    pcVar7 = &DAT_0a941eaf + iVar2;
    do {
      pcVar3 = pcVar7 + 1;
      pcVar7 = pcVar7 + 1;
    } while (*pcVar3 != '\0');
    pcVar3 = local_410;
    for (uVar6 = uVar8 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar7 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  if ((param_3 & 4) != 0) {
    pcVar7 = local_410;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar7[(int)(destination + (-1 - (int)local_410))] = cVar1;
    } while (cVar1 != '\0');
    __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
    return;
  }
LAB_0049b67a:
  __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 0049b970; extra-producers */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0049b970(int param_1,int param_2,int param_3,int param_4,byte param_5)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char local_78 [108];
  uint local_c;
  
  local_c = DAT_005e200c ^ (uint)&stack0xfffffffc;
  DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  iVar3 = DAT_0a84b7a8 * 0x400;
  memset(&DAT_0a941eb0 + iVar3,0,0x400);
  _CIatan2();
  iVar4 = FUN_004cf520();
  DAT_0a624eac = iVar4;
  memset(local_78,0,100);
  uVar2 = s_directly_0059db44._8_2_;
  pcVar5 = (&PTR_DAT_0058e710)[iVar4];
  iVar4 = -(int)pcVar5;
  do {
    cVar1 = *pcVar5;
    pcVar5[(int)(local_78 + iVar4)] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  if (((param_5 & 2) == 0) &&
     (((param_1 == param_3 || (param_2 == param_4)) ||
      (uVar6 = param_1 - param_3 >> 0x1f, uVar7 = param_2 - param_4 >> 0x1f,
      (param_1 - param_3 ^ uVar6) - uVar6 == (param_2 - param_4 ^ uVar7) - uVar7)))) {
    if ((param_5 & 4) != 0) goto LAB_0049bab0;
    *(undefined8 *)(&DAT_0a941eb0 + iVar3) = s_directly_0059db44._0_8_;
    *(undefined2 *)(&DAT_0a941eb8 + iVar3) = uVar2;
  }
  if ((param_5 & 4) == 0) {
    pcVar5 = &DAT_0a941eaf + iVar3;
    do {
      pcVar8 = pcVar5;
      pcVar5 = pcVar8 + 1;
    } while (pcVar8[1] != '\0');
    *(undefined4 *)(pcVar8 + 1) = s_in_the_0059db50._0_4_;
    *(undefined4 *)(pcVar8 + 5) = s_in_the_0059db50._4_4_;
  }
LAB_0049bab0:
  pcVar5 = local_78;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  uVar6 = (int)pcVar5 - (int)local_78;
  pcVar5 = &DAT_0a941eaf + iVar3;
  do {
    pcVar8 = pcVar5 + 1;
    pcVar5 = pcVar5 + 1;
  } while (*pcVar8 != '\0');
  pcVar8 = local_78;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar5 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar5 = pcVar5 + 1;
  }
  if ((param_5 & 1) != 0) {
    pcVar5 = &DAT_0a941eaf + iVar3;
    do {
      pcVar8 = pcVar5;
      pcVar5 = pcVar8 + 1;
    } while (pcVar8[1] != '\0');
    *(undefined4 *)(pcVar8 + 1) = s_from_here_0059db58._0_4_;
    *(undefined4 *)(pcVar8 + 5) = s_from_here_0059db58._4_4_;
    *(undefined2 *)(pcVar8 + 9) = s_from_here_0059db58._8_2_;
    pcVar8[0xb] = s_from_here_0059db58[10];
  }
  __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 00549000; extra-producers */

void FUN_00549000(undefined1 *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 extraout_ECX;
  uint uVar6;
  byte *pbVar7;
  uint uVar8;
  char *pcVar9;
  byte *pbVar10;
  char *pcVar11;
  undefined8 uVar12;
  byte local_40c [1028];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  FUN_00548f30();
  uVar12 = FUN_00548740(10,200,extraout_ECX,param_2,param_3);
  if ((int)uVar12 != 0) {
    sprintf(param_1 + 1,"knowledge about treasure %s",&DAT_0a621028);
    uVar3 = s_There_is_a_treasure_you_know_and_005b7d34._12_4_;
    uVar2 = s_There_is_a_treasure_you_know_and_005b7d34._8_4_;
    uVar5 = s_There_is_a_treasure_you_know_and_005b7d34._4_4_;
    *(undefined4 *)(param_1 + 0x65) = s_There_is_a_treasure_you_know_and_005b7d34._0_4_;
    *(undefined4 *)(param_1 + 0x69) = uVar5;
    *(undefined4 *)(param_1 + 0x6d) = uVar2;
    *(undefined4 *)(param_1 + 0x71) = uVar3;
    uVar3 = s_There_is_a_treasure_you_know_and_005b7d34._28_4_;
    uVar2 = s_There_is_a_treasure_you_know_and_005b7d34._24_4_;
    uVar5 = s_There_is_a_treasure_you_know_and_005b7d34._20_4_;
    *(undefined4 *)(param_1 + 0x75) = s_There_is_a_treasure_you_know_and_005b7d34._16_4_;
    *(undefined4 *)(param_1 + 0x79) = uVar5;
    *(undefined4 *)(param_1 + 0x7d) = uVar2;
    *(undefined4 *)(param_1 + 0x81) = uVar3;
    uVar3 = s_There_is_a_treasure_you_know_and_005b7d34._44_4_;
    uVar2 = s_There_is_a_treasure_you_know_and_005b7d34._40_4_;
    uVar5 = s_There_is_a_treasure_you_know_and_005b7d34._36_4_;
    *(undefined4 *)(param_1 + 0x85) = s_There_is_a_treasure_you_know_and_005b7d34._32_4_;
    *(undefined4 *)(param_1 + 0x89) = uVar5;
    *(undefined4 *)(param_1 + 0x8d) = uVar2;
    *(undefined4 *)(param_1 + 0x91) = uVar3;
    *(undefined4 *)(param_1 + 0x95) = s_There_is_a_treasure_you_know_and_005b7d34._48_4_;
    *(undefined2 *)(param_1 + 0x99) = s_There_is_a_treasure_you_know_and_005b7d34._52_2_;
    iVar4 = tolower((uint)DAT_0a621ac8);
    DAT_0a621ac8 = (byte)iVar4;
    sprintf(param_1 + 0xc9,
            "I have heard there\'s a treasure %s. If you care to help me, I can tell you where it\'s said to be hidden. There is %s to be found."
            ,&DAT_0a621028,&DAT_0a620ef8);
    uVar3 = s_Now_how_about_that_treasure__005b7df4._12_4_;
    uVar2 = s_Now_how_about_that_treasure__005b7df4._8_4_;
    uVar5 = s_Now_how_about_that_treasure__005b7df4._4_4_;
    *(undefined4 *)(param_1 + 0x259) = s_Now_how_about_that_treasure__005b7df4._0_4_;
    *(undefined4 *)(param_1 + 0x25d) = uVar5;
    *(undefined4 *)(param_1 + 0x261) = uVar2;
    *(undefined4 *)(param_1 + 0x265) = uVar3;
    *(undefined8 *)(param_1 + 0x269) = s_Now_how_about_that_treasure__005b7df4._16_8_;
    *(undefined4 *)(param_1 + 0x271) = s_Now_how_about_that_treasure__005b7df4._24_4_;
    param_1[0x275] = s_Now_how_about_that_treasure__005b7df4[0x1c];
    uVar5 = FUN_0049c760();
    sprintf(param_1 + 0x2bd,"There\'s a treasure %s %s.",&DAT_0a621b60,uVar5);
    sprintf((char *)local_40c," It is %s, %s.",&DAT_0a620e90,&DAT_0a620f90);
    pbVar7 = local_40c;
    do {
      bVar1 = *pbVar7;
      pbVar7 = pbVar7 + 1;
    } while (bVar1 != 0);
    uVar8 = (int)pbVar7 - (int)local_40c;
    pbVar7 = param_1 + 700;
    do {
      pbVar10 = pbVar7 + 1;
      pbVar7 = pbVar7 + 1;
    } while (*pbVar10 != 0);
    pbVar10 = local_40c;
    for (uVar6 = uVar8 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pbVar7 = *(undefined4 *)pbVar10;
      pbVar10 = pbVar10 + 4;
      pbVar7 = pbVar7 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pbVar7 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      pbVar7 = pbVar7 + 1;
    }
    sprintf((char *)local_40c," They say there is %s to be found.",&DAT_0a620ef8);
    pbVar7 = local_40c;
    do {
      bVar1 = *pbVar7;
      pbVar7 = pbVar7 + 1;
    } while (bVar1 != 0);
    uVar8 = (int)pbVar7 - (int)local_40c;
    pbVar7 = param_1 + 700;
    do {
      pbVar10 = pbVar7 + 1;
      pbVar7 = pbVar7 + 1;
    } while (*pbVar10 != 0);
    pbVar10 = local_40c;
    for (uVar6 = uVar8 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pbVar7 = *(undefined4 *)pbVar10;
      pbVar10 = pbVar10 + 4;
      pbVar7 = pbVar7 + 4;
    }
    pcVar9 = param_1 + 700;
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pbVar7 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      pbVar7 = pbVar7 + 1;
    }
    do {
      pcVar11 = pcVar9 + 1;
      pcVar9 = pcVar9 + 1;
    } while (*pcVar11 != '\0');
    pcVar11 = " I wish you all the luck finding it!";
    for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar9 = pcVar9 + 4;
    }
    *pcVar9 = *pcVar11;
    iVar4 = 0;
    uVar8 = rand();
    uVar8 = uVar8 & 0x8000000f;
    if ((int)uVar8 < 0) {
      uVar8 = (uVar8 - 1 | 0xfffffff0) + 1;
    }
    do {
      uVar6 = rand();
      uVar6 = uVar6 & 0x8000000f;
      if ((int)uVar6 < 0) {
        uVar6 = (uVar6 - 1 | 0xfffffff0) + 1;
      }
      iVar4 = iVar4 + 1;
      if (iVar4 == 10) {
        uVar8 = 0xffffffff;
      }
    } while (uVar6 == uVar8);
    iVar4 = 0;
    *(uint *)(param_4 + 0x23c) = uVar6 + (int)uVar12 + -8;
    uVar8 = rand();
    uVar8 = uVar8 & 0x8000000f;
    if ((int)uVar8 < 0) {
      uVar8 = (uVar8 - 1 | 0xfffffff0) + 1;
    }
    do {
      uVar6 = rand();
      uVar6 = uVar6 & 0x8000000f;
      if ((int)uVar6 < 0) {
        uVar6 = (uVar6 - 1 | 0xfffffff0) + 1;
      }
      iVar4 = iVar4 + 1;
      if (iVar4 == 10) {
        uVar8 = 0xffffffff;
      }
    } while (uVar6 == uVar8);
    *(uint *)(param_4 + 0x240) = uVar6 + (int)((ulonglong)uVar12 >> 0x20) + -8;
    iVar4 = 0;
    do {
      bVar1 = (&DAT_0a621ac8)[iVar4];
      local_40c[iVar4] = bVar1;
      iVar4 = iVar4 + 1;
    } while (bVar1 != 0);
    iVar4 = toupper((uint)local_40c[0]);
    pbVar7 = local_40c;
    local_40c[0] = (byte)iVar4;
    param_4 = param_4 - (int)pbVar7;
    do {
      bVar1 = *pbVar7;
      pbVar7 = pbVar7 + 1;
      pbVar7[param_4 + 0x243] = bVar1;
    } while (bVar1 != 0);
    *(undefined8 *)(param_1 + 0x44d) = s__info___xarea__005b7e8c._0_8_;
    *(undefined4 *)(param_1 + 0x455) = s__info___xarea__005b7e8c._8_4_;
    *(undefined2 *)(param_1 + 0x459) = s__info___xarea__005b7e8c._12_2_;
    param_1[0x45b] = s__info___xarea__005b7e8c[0xe];
    *param_1 = 1;
    __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
    return;
  }
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 00549330; extra-producers */

void FUN_00549330(undefined1 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined4 local_428;
  undefined4 local_424;
  char *local_420;
  int local_41c;
  undefined4 local_418;
  undefined4 local_414;
  char local_410 [1028];
  uint local_c;
  
  local_c = DAT_005e200c ^ (uint)&stack0xfffffffc;
  local_414 = 0;
  local_418 = 0;
  local_428 = 0;
  local_424 = 0;
  FUN_00548f30();
  uVar1 = s_What_kind_of_spells_are_you_talk_005b7e9c._12_4_;
  uVar11 = s_What_kind_of_spells_are_you_talk_005b7e9c._8_4_;
  uVar10 = s_What_kind_of_spells_are_you_talk_005b7e9c._4_4_;
  iVar12 = 0;
  *(undefined4 *)(param_1 + 0x65) = s_What_kind_of_spells_are_you_talk_005b7e9c._0_4_;
  *(undefined4 *)(param_1 + 0x69) = uVar10;
  *(undefined4 *)(param_1 + 0x6d) = uVar11;
  *(undefined4 *)(param_1 + 0x71) = uVar1;
  uVar1 = s_What_kind_of_spells_are_you_talk_005b7e9c._28_4_;
  uVar11 = s_What_kind_of_spells_are_you_talk_005b7e9c._24_4_;
  uVar10 = s_What_kind_of_spells_are_you_talk_005b7e9c._20_4_;
  *(undefined4 *)(param_1 + 0x75) = s_What_kind_of_spells_are_you_talk_005b7e9c._16_4_;
  *(undefined4 *)(param_1 + 0x79) = uVar10;
  *(undefined4 *)(param_1 + 0x7d) = uVar11;
  *(undefined4 *)(param_1 + 0x81) = uVar1;
  *(undefined8 *)(param_1 + 0x85) = s_What_kind_of_spells_are_you_talk_005b7e9c._32_8_;
  *(undefined2 *)(param_1 + 0x8d) = s_What_kind_of_spells_are_you_talk_005b7e9c._40_2_;
  param_1[0x8f] = s_What_kind_of_spells_are_you_talk_005b7e9c[0x2a];
  uVar6 = rand();
  uVar6 = uVar6 & 0x80000001;
  if ((int)uVar6 < 0) {
    uVar6 = (uVar6 - 1 | 0xfffffffe) + 1;
  }
  do {
    uVar7 = rand();
    uVar7 = uVar7 & 0x80000001;
    if ((int)uVar7 < 0) {
      uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
    }
    iVar12 = iVar12 + 1;
    if (iVar12 == 10) {
      uVar6 = 0xffffffff;
    }
  } while (uVar7 == uVar6);
  if (uVar7 == 0) {
    iVar12 = 0x32;
    pcVar8 = strstr(local_420,"[hunting]");
    local_41c = iVar12;
    if (pcVar8 == (char *)0x0) {
      iVar12 = 100;
      local_41c = iVar12;
    }
  }
  else {
    iVar12 = 100;
    local_41c = 100;
    pcVar8 = strstr(local_420,"[fishing]");
    if (pcVar8 == (char *)0x0) {
      iVar12 = 0x32;
      local_41c = iVar12;
    }
  }
  cVar5 = FUN_004e80d0(&local_414,&local_418,&local_428,&local_424);
  if (cVar5 == '\0') {
    *param_1 = 0;
    __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
    return;
  }
  pcVar9 = (char *)FUN_004e7f90();
  pcVar8 = pcVar9;
  do {
    cVar5 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar8[(int)(local_410 + (-1 - (int)pcVar9))] = cVar5;
  } while (cVar5 != '\0');
  *(undefined8 *)(param_1 + 1) = s_some_spells_005b7ee0._0_8_;
  *(undefined4 *)(param_1 + 9) = s_some_spells_005b7ee0._8_4_;
  uVar4 = s_some_fishing_spells_005b7f08._12_4_;
  uVar3 = s_some_fishing_spells_005b7f08._8_4_;
  uVar2 = s_some_fishing_spells_005b7f08._4_4_;
  uVar1 = s_some_old_woodsman_spells_005b7eec._12_4_;
  uVar11 = s_some_old_woodsman_spells_005b7eec._8_4_;
  uVar10 = s_some_old_woodsman_spells_005b7eec._4_4_;
  if (iVar12 == 0x32) {
    *(undefined4 *)(param_1 + 1) = s_some_old_woodsman_spells_005b7eec._0_4_;
    *(undefined4 *)(param_1 + 5) = uVar10;
    *(undefined4 *)(param_1 + 9) = uVar11;
    *(undefined4 *)(param_1 + 0xd) = uVar1;
    *(undefined8 *)(param_1 + 0x11) = s_some_old_woodsman_spells_005b7eec._16_8_;
    param_1[0x19] = s_some_old_woodsman_spells_005b7eec[0x18];
  }
  else if (iVar12 == 100) {
    *(undefined4 *)(param_1 + 1) = s_some_fishing_spells_005b7f08._0_4_;
    *(undefined4 *)(param_1 + 5) = uVar2;
    *(undefined4 *)(param_1 + 9) = uVar3;
    *(undefined4 *)(param_1 + 0xd) = uVar4;
    *(undefined4 *)(param_1 + 0x11) = s_some_fishing_spells_005b7f08._16_4_;
  }
  uVar10 = FUN_004e7ef0();
  sprintf(param_1 + 0xc9,"It\'s spell about %s.",uVar10);
  if (iVar12 == 0x32) {
    uVar10 = FUN_004e7ef0();
    pcVar8 = "It\'s just a spell a hunter might appreciate. About %s.";
LAB_00549555:
    sprintf(param_1 + 0xc9,pcVar8,uVar10);
  }
  else if (iVar12 == 100) {
    uVar10 = FUN_004e7ef0();
    pcVar8 = "It\'s just a spell for a fisherman who wants to learn about %s.";
    goto LAB_00549555;
  }
  puVar13 = (undefined4 *)(param_1 + 200);
  do {
    pcVar8 = (char *)((int)puVar13 + 1);
    puVar13 = (undefined4 *)((int)puVar13 + 1);
  } while (*pcVar8 != '\0');
  pcVar8 = " I can reveal it to you as a favour in return, if that pleases you.";
  for (iVar12 = 0x11; iVar12 != 0; iVar12 = iVar12 + -1) {
    *puVar13 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    puVar13 = puVar13 + 1;
  }
  sprintf(param_1 + 0x2bd,"I hope this spell finds you well. %s",local_410);
  uVar10 = local_418;
  if (local_41c == 0x32) {
    uVar11 = FUN_004e7f90();
    pcVar8 = "I hope this will help you on your future hunting days. %s";
  }
  else {
    if (local_41c != 100) goto LAB_005495d6;
    uVar11 = FUN_004e7f90();
    pcVar8 = "I hope this suits you on your future fishing days. %s";
  }
  sprintf(param_1 + 0x2bd,pcVar8,uVar11);
LAB_005495d6:
  sprintf(param_1 + 0x44d,"[info] [magicmeans:%d] [magicvar:%d]",local_414,uVar10);
  uVar1 = s_Now_how_about_that_spell__005b80b8._12_4_;
  uVar11 = s_Now_how_about_that_spell__005b80b8._8_4_;
  uVar10 = s_Now_how_about_that_spell__005b80b8._4_4_;
  *(undefined4 *)(param_1 + 0x259) = s_Now_how_about_that_spell__005b80b8._0_4_;
  *(undefined4 *)(param_1 + 0x25d) = uVar10;
  *(undefined4 *)(param_1 + 0x261) = uVar11;
  *(undefined4 *)(param_1 + 0x265) = uVar1;
  *(undefined8 *)(param_1 + 0x269) = s_Now_how_about_that_spell__005b80b8._16_8_;
  *(undefined2 *)(param_1 + 0x271) = s_Now_how_about_that_spell__005b80b8._24_2_;
  *param_1 = 1;
  __security_check_cookie(local_c ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 00549640; extra-producers */

void __fastcall FUN_00549640(int param_1,int param_2,undefined1 *param_3)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  double dVar8;
  int local_418;
  undefined8 local_40c;
  char local_404 [1020];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  FUN_00548f30();
  local_418 = 0;
  do {
    iVar6 = 0;
    local_40c._0_6_ = CONCAT24(DAT_00590530,DAT_0059052c);
    iVar3 = rand();
    iVar3 = iVar3 % 7;
    do {
      iVar4 = rand();
      iVar6 = iVar6 + 1;
      if (iVar6 == 10) {
        iVar3 = -1;
      }
    } while (iVar4 % 7 == iVar3);
    switch(iVar4 % 7) {
    case 0:
      local_40c._0_1_ = s_TRAPPING_0058d2dc[0];
      local_40c._1_1_ = s_TRAPPING_0058d2dc[1];
      local_40c._2_1_ = s_TRAPPING_0058d2dc[2];
      local_40c._3_1_ = s_TRAPPING_0058d2dc[3];
      local_40c._4_1_ = s_TRAPPING_0058d2dc[4];
      local_40c._5_1_ = s_TRAPPING_0058d2dc[5];
      local_40c._6_1_ = s_TRAPPING_0058d2dc[6];
      local_40c._7_1_ = s_TRAPPING_0058d2dc[7];
      local_404[0] = s_TRAPPING_0058d2dc[8];
      break;
    case 1:
      local_40c._0_1_ = s_TRACKING_005905f4[0];
      local_40c._1_1_ = s_TRACKING_005905f4[1];
      local_40c._2_1_ = s_TRACKING_005905f4[2];
      local_40c._3_1_ = s_TRACKING_005905f4[3];
      local_40c._4_1_ = s_TRACKING_005905f4[4];
      local_40c._5_1_ = s_TRACKING_005905f4[5];
      local_40c._6_1_ = s_TRACKING_005905f4[6];
      local_40c._7_1_ = s_TRACKING_005905f4[7];
      local_404[0] = s_TRACKING_005905f4[8];
      break;
    case 2:
      local_40c._4_1_ = s_FISHING_005905b0[4];
      local_40c._5_1_ = s_FISHING_005905b0[5];
      local_40c._6_1_ = s_FISHING_005905b0[6];
      local_40c._7_1_ = s_FISHING_005905b0[7];
      local_40c._0_1_ = s_FISHING_005905b0[0];
      local_40c._1_1_ = s_FISHING_005905b0[1];
      local_40c._2_1_ = s_FISHING_005905b0[2];
      local_40c._3_1_ = s_FISHING_005905b0[3];
      break;
    case 3:
      local_40c._0_1_ = 'B';
      local_40c._1_1_ = 'O';
      local_40c._2_1_ = 'W';
      local_40c._3_1_ = '\0';
      break;
    case 4:
      local_40c._0_1_ = s_HIDEWORKING_005905e8[0];
      local_40c._1_1_ = s_HIDEWORKING_005905e8[1];
      local_40c._2_1_ = s_HIDEWORKING_005905e8[2];
      local_40c._3_1_ = s_HIDEWORKING_005905e8[3];
      local_40c._4_1_ = s_HIDEWORKING_005905e8[4];
      local_40c._5_1_ = s_HIDEWORKING_005905e8[5];
      local_40c._6_1_ = s_HIDEWORKING_005905e8[6];
      local_40c._7_1_ = s_HIDEWORKING_005905e8[7];
      local_404[0] = s_HIDEWORKING_005905e8[8];
      local_404[1] = s_HIDEWORKING_005905e8[9];
      local_404[2] = s_HIDEWORKING_005905e8[10];
      local_404[3] = s_HIDEWORKING_005905e8[0xb];
      break;
    case 5:
      local_40c._0_1_ = s_HERBLORE_005905dc[0];
      local_40c._1_1_ = s_HERBLORE_005905dc[1];
      local_40c._2_1_ = s_HERBLORE_005905dc[2];
      local_40c._3_1_ = s_HERBLORE_005905dc[3];
      local_40c._4_1_ = s_HERBLORE_005905dc[4];
      local_40c._5_1_ = s_HERBLORE_005905dc[5];
      local_40c._6_1_ = s_HERBLORE_005905dc[6];
      local_40c._7_1_ = s_HERBLORE_005905dc[7];
      local_404[0] = s_HERBLORE_005905dc[8];
      break;
    default:
      local_40c._4_1_ = s_SPEAR_00590548[4];
      local_40c._5_1_ = s_SPEAR_00590548[5];
      local_40c._0_1_ = s_SPEAR_00590548[0];
      local_40c._1_1_ = s_SPEAR_00590548[1];
      local_40c._2_1_ = s_SPEAR_00590548[2];
      local_40c._3_1_ = s_SPEAR_00590548[3];
    }
    if ((&DAT_061514bc)[param_1 * 0x15a] == 0x226) {
      iVar6 = 0;
      iVar3 = rand();
      iVar3 = iVar3 % 6;
      do {
        iVar4 = rand();
        iVar6 = iVar6 + 1;
        if (iVar6 == 10) {
          iVar3 = -1;
        }
      } while (iVar4 % 6 == iVar3);
      uVar2 = local_40c._4_4_;
      switch(iVar4 % 6) {
      case 0:
        local_40c._4_1_ = s_STEALTH_00590580[4];
        local_40c._5_1_ = s_STEALTH_00590580[5];
        local_40c._6_1_ = s_STEALTH_00590580[6];
        local_40c._7_1_ = s_STEALTH_00590580[7];
        local_40c._0_1_ = s_STEALTH_00590580[0];
        local_40c._1_1_ = s_STEALTH_00590580[1];
        local_40c._2_1_ = s_STEALTH_00590580[2];
        local_40c._3_1_ = s_STEALTH_00590580[3];
        break;
      case 1:
        local_40c._0_1_ = s_TRACKING_005905f4[0];
        local_40c._1_1_ = s_TRACKING_005905f4[1];
        local_40c._2_1_ = s_TRACKING_005905f4[2];
        local_40c._3_1_ = s_TRACKING_005905f4[3];
        local_40c._4_1_ = s_TRACKING_005905f4[4];
        local_40c._5_1_ = s_TRACKING_005905f4[5];
        local_40c._6_1_ = s_TRACKING_005905f4[6];
        local_40c._7_1_ = s_TRACKING_005905f4[7];
        local_404[0] = s_TRACKING_005905f4[8];
        break;
      case 2:
        local_40c._0_1_ = 'B';
        local_40c._1_1_ = 'O';
        local_40c._2_1_ = 'W';
        local_40c._3_1_ = '\0';
        local_40c = CONCAT44(uVar2,(undefined4)local_40c);
        break;
      case 3:
        local_40c._4_1_ = s_SWORD_00590534[4];
        local_40c._5_1_ = s_SWORD_00590534[5];
        local_40c._0_1_ = s_SWORD_00590534[0];
        local_40c._1_1_ = s_SWORD_00590534[1];
        local_40c._2_1_ = s_SWORD_00590534[2];
        local_40c._3_1_ = s_SWORD_00590534[3];
        break;
      default:
        local_40c._4_1_ = s_SPEAR_00590548[4];
        local_40c._5_1_ = s_SPEAR_00590548[5];
        local_40c._0_1_ = s_SPEAR_00590548[0];
        local_40c._1_1_ = s_SPEAR_00590548[1];
        local_40c._2_1_ = s_SPEAR_00590548[2];
        local_40c._3_1_ = s_SPEAR_00590548[3];
        break;
      case 5:
        local_40c._4_1_ = (undefined1)DAT_00590530;
        local_40c._5_1_ = DAT_00590530._1_1_;
        local_40c._0_1_ = (undefined1)DAT_0059052c;
        local_40c._1_1_ = DAT_0059052c._1_1_;
        local_40c._2_1_ = DAT_0059052c._2_1_;
        local_40c._3_1_ = DAT_0059052c._3_1_;
      }
    }
    iVar3 = FUN_0051b450();
    if (0x50 < iVar3) {
      memset(&local_40c,0,0x400);
    }
    pcVar5 = (char *)&local_40c;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
  } while ((pcVar5 == (char *)((int)&local_40c + 1)) && (local_418 = local_418 + 1, local_418 < 10))
  ;
  pcVar5 = (char *)&local_40c;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  if (pcVar5 == (char *)((int)&local_40c + 1)) {
    __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
    return;
  }
  Lowercase((char *)&local_40c);
  sprintf(param_3 + 1,"a %s lesson");
  Lowercase((char *)&local_40c);
  sprintf(param_3 + 0x65,"You could teach me some %s skills?");
  iVar3 = FUN_0051b450();
  dVar8 = (double)((iVar3 + 5) / 10);
  if (iVar3 < 0x28) {
    ceil(dVar8);
    pcVar5 = Lowercase((char *)&local_40c);
    sprintf(param_3 + 0xc9,"I reckon your %s skills are of %s level so I could surely ",pcVar5);
  }
  else {
    dVar8 = ceil(dVar8);
    iVar3 = (int)dVar8;
    if (10 < iVar3) {
      iVar3 = 10;
    }
    pcVar5 = Lowercase((char *)&local_40c);
    sprintf(param_3 + 0xc9,"I trust you are %s already, but with my %s experience I could ",
            s_unskilled_005e9f50 + iVar3 * 100,pcVar5);
  }
  puVar7 = (undefined4 *)(param_3 + 200);
  do {
    pcVar5 = (char *)((int)puVar7 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  } while (*pcVar5 != '\0');
  pcVar5 = "teach you to improve with that a bit more.";
  for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    puVar7 = puVar7 + 1;
  }
  *(undefined2 *)puVar7 = *(undefined2 *)pcVar5;
  *(char *)((int)puVar7 + 2) = pcVar5[2];
  Lowercase((char *)&local_40c);
  sprintf(param_3 + 0x2bd,"It\'s some %s instructions for you then.");
  *(undefined8 *)(param_3 + 0x44d) = s__claim_reward__005b33f8._0_8_;
  *(undefined4 *)(param_3 + 0x455) = s__claim_reward__005b33f8._8_4_;
  *(undefined2 *)(param_3 + 0x459) = s__claim_reward__005b33f8._12_2_;
  param_3[0x45b] = s__claim_reward__005b33f8[0xe];
  Lowercase((char *)&local_40c);
  sprintf(param_3 + 0x259,"Now I\'m eager to have that %s lesson.");
  pcVar5 = (char *)&local_40c;
  *param_3 = 1;
  *(undefined1 *)(param_2 + 0xf0cd) = 1;
  param_2 = param_2 - (int)pcVar5;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar5[param_2 + 0xf0cd] = cVar1;
  } while (cVar1 != '\0');
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 0049c760; nested-producers */

char * FUN_0049c760(void)

{
  char *destination;
  undefined4 uVar1;
  undefined4 extraout_ECX;
  
  DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  destination = &DAT_0a941eb0 + DAT_0a84b7a8 * 0x400;
  memset(destination,0,0x400);
  uVar1 = FUN_0055ec00();
  uVar1 = FUN_0049b040(1,extraout_ECX,uVar1);
  sprintf(destination,"%s %s",uVar1);
  return destination;
}



/* Extracted native producer 004e7ef0; nested-producers */

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_004e7ef0(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  undefined1 local_106c [2096];
  undefined4 local_83c [3];
  char local_82f [2087];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  iVar2 = DAT_0a84b7a8 * 0x400;
  memset(&DAT_0a941eb0 + iVar2,0,0x400);
  puVar3 = (undefined4 *)FUN_004e76c0(local_106c);
  puVar6 = local_83c;
  for (iVar4 = 0x20c; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar6 = puVar6 + 1;
  }
  pcVar5 = local_82f;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar5[(int)(&DAT_0a941eb0 + iVar2 + (-1 - (int)local_82f))] = cVar1;
  } while (cVar1 != '\0');
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 004e7f90; nested-producers */

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void __fastcall FUN_004e7f90(undefined4 param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  undefined1 local_1074 [2100];
  uint local_840;
  undefined4 local_83c [23];
  char local_7df [2007];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  iVar2 = DAT_0a84b7a8 * 0x400;
  local_840 = param_2;
  memset(&DAT_0a941eb0 + iVar2,0,0x400);
  puVar3 = (undefined4 *)FUN_004e76c0(local_1074);
  puVar6 = local_83c;
  for (iVar4 = 0x20c; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar6 = puVar6 + 1;
  }
  if (local_840 < 5) {
    pcVar5 = local_7df + local_840 * 400;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar5[(int)(&DAT_0a941eb0 + iVar2 + (-1 - (int)(local_7df + local_840 * 400)))] = cVar1;
    } while (cVar1 != '\0');
  }
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 004e80d0; nested-producers */

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void __fastcall
FUN_004e80d0(undefined4 param_1,char *param_2,int *param_3,undefined4 *param_4,undefined4 *param_5,
            undefined4 *param_6)

{
  byte bVar1;
  char cVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  undefined4 *puVar9;
  uint uVar10;
  int iVar11;
  undefined1 local_1a4c [2096];
  undefined4 local_121c;
  byte local_1218;
  byte local_1217;
  char local_1215;
  undefined4 *local_9e8;
  undefined4 *local_9e4;
  int *local_9e0;
  uint local_9dc;
  undefined4 *local_9d8;
  char *local_9d4;
  uint local_9d0;
  int local_9cc;
  char local_9c6;
  byte local_9c5;
  int local_9c4 [256];
  int local_5c4 [19];
  char cStack_575;
  char local_574 [1024];
  byte local_174 [256];
  char local_74 [108];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  local_9d8 = param_6;
  local_9e0 = param_3;
  local_9e4 = param_4;
  local_9e8 = param_5;
  local_9cc = 0;
  local_9d4 = param_2;
  memset(local_9c4,0,0x400);
  memset(local_174,0,0x100);
  *param_3 = 0;
  *param_4 = 0;
  *param_5 = 0;
  *local_9d8 = 0;
  memset(local_574,0,0x400);
  local_5c4[0] = 0;
  local_5c4[1] = 0;
  local_5c4[2] = 0;
  local_5c4[3] = 0;
  iVar6 = 0;
  do {
    puVar3 = (undefined4 *)FUN_004e76c0(local_1a4c);
    uVar7 = local_9dc;
    local_9c5 = '\0';
    puVar9 = &local_121c;
    for (iVar5 = 0x20c; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar9 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar9 = puVar9 + 1;
    }
    if ((uVar7 != 0) && (local_1218 != uVar7)) {
      local_1217 = 0;
    }
    if ((local_1215 == '\0') && (local_1217 != 0)) {
      uVar10 = (uint)local_1217;
      uVar7 = 0;
      if (uVar10 != 0) {
        local_9d0 = 1;
        do {
          local_9c6 = '\0';
          if (((0xff < iVar6) || (5 < (int)uVar7)) ||
             (((&DAT_0a72bbdf)[iVar6] & (byte)local_9d0) == 0)) {
            local_9c6 = '\x01';
          }
          sprintf(local_74,"[%d.%d]",iVar6,uVar7);
          if (((local_9d4 == (char *)0x0) ||
              (pcVar4 = strstr(local_9d4,local_74), pcVar4 == (char *)0x0)) && (local_9c6 != '\0'))
          {
            bVar1 = local_174[local_9cc];
            local_9c4[local_9cc] = iVar6;
            local_174[local_9cc] = bVar1 | (byte)(1 << (uVar7 & 0x1f));
            local_9c5 = '\x01';
          }
          uVar7 = uVar7 + 1;
          local_9d0 = local_9d0 << 1 | (uint)((int)local_9d0 < 0);
        } while ((int)uVar7 < (int)uVar10);
        if (local_9c5 != '\0') {
          local_9cc = local_9cc + 1;
        }
      }
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x100);
  if (local_9cc == 0) {
    __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
    return;
  }
  local_9c5 = 0;
  local_9d0 = 10;
  do {
    iVar6 = local_9cc;
    iVar11 = 0;
    iVar5 = rand();
    pcVar4 = (char *)(iVar5 % iVar6);
    do {
      iVar5 = rand();
      iVar11 = iVar11 + 1;
      local_9d4 = (char *)(iVar5 % iVar6);
      if (iVar11 == 10) {
        pcVar4 = (char *)0xffffffff;
      }
    } while (local_9d4 == pcVar4);
    iVar5 = 0;
    iVar6 = rand();
    iVar6 = iVar6 % 5;
    do {
      iVar11 = rand();
      iVar11 = iVar11 % 5;
      iVar5 = iVar5 + 1;
      if (iVar5 == 10) {
        iVar6 = -1;
      }
    } while (iVar11 == iVar6);
    iVar6 = 0;
    do {
      if (((uint)local_174[(int)local_9d4] & 1 << ((byte)iVar11 & 0x1f)) != 0) {
        local_9d4 = (char *)local_9c4[(int)local_9d4];
        sprintf(local_74,"[%d.%d]",local_9d4,iVar11);
        pcVar4 = strstr(local_574,local_74);
        if (pcVar4 == (char *)0x0) {
          pcVar4 = local_74;
          do {
            cVar2 = *pcVar4;
            pcVar4 = pcVar4 + 1;
          } while (cVar2 != '\0');
          uVar7 = (int)pcVar4 - (int)local_74;
          pcVar4 = &cStack_575;
          do {
            pcVar8 = pcVar4 + 1;
            pcVar4 = pcVar4 + 1;
          } while (*pcVar8 != '\0');
          pcVar8 = local_74;
          for (uVar10 = uVar7 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pcVar4 = *(undefined4 *)pcVar8;
            pcVar8 = pcVar8 + 4;
            pcVar4 = pcVar4 + 4;
          }
          uVar10 = (uint)local_9c5;
          for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *pcVar4 = *pcVar8;
            pcVar8 = pcVar8 + 1;
            pcVar4 = pcVar4 + 1;
          }
          local_9c5 = local_9c5 + 1;
          local_5c4[uVar10 * 2] = (int)local_9d4;
          local_5c4[uVar10 * 2 + 1] = iVar11;
        }
        break;
      }
      iVar11 = iVar11 + 1;
      if (4 < iVar11) {
        iVar11 = 0;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 5);
    local_9d0 = local_9d0 + -1;
    if (local_9d0 == 0) {
      *local_9e0 = local_5c4[0];
      *local_9e4 = local_5c4[1];
      *local_9e8 = local_5c4[2];
      *local_9d8 = local_5c4[3];
      __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc,local_9c5);
      return;
    }
  } while( true );
}



/* Extracted native producer 00548740; nested-producers */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall
FUN_00548740(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,int param_7)

{
  undefined *_Dst;
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 *puVar8;
  uint uVar9;
  int extraout_ECX;
  uint uVar10;
  char *pcVar11;
  uint uVar12;
  int iVar13;
  undefined8 uVar14;
  undefined4 local_5d8;
  undefined4 local_5d4;
  int local_56c;
  undefined4 local_564;
  uint local_560;
  uint local_55c;
  char local_558 [1024];
  undefined8 local_158;
  undefined1 local_150;
  undefined1 uStack_f1;
  undefined8 local_f0;
  char local_e8 [4];
  char local_e4;
  char cStack_89;
  char local_88 [104];
  undefined8 local_20;
  undefined8 uStack_18;
  undefined4 local_10;
  uint local_c;
  
  local_c = DAT_005e200c ^ (uint)&stack0xfffffffc;
  local_56c = param_7;
  uVar12 = DAT_0a84b7a8 + 1 & 0x800003ff;
  if ((int)uVar12 < 0) {
    uVar12 = (uVar12 - 1 | 0xfffffc00) + 1;
  }
  local_564 = param_2;
  memset(&DAT_0a941eb0 + uVar12 * 0x400,0,0x400);
  uVar12 = uVar12 + 1 & 0x800003ff;
  if ((int)uVar12 < 0) {
    uVar12 = (uVar12 - 1 | 0xfffffc00) + 1;
  }
  memset(&DAT_0a941eb0 + uVar12 * 0x400,0,0x400);
  DAT_0a84b7a8 = uVar12 + 1 & 0x800003ff;
  if ((int)DAT_0a84b7a8 < 0) {
    DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
  }
  memset(&DAT_0a941eb0 + DAT_0a84b7a8 * 0x400,0,0x400);
  memset(local_88,0,100);
  local_10 = 0;
  local_20 = 0;
  uStack_18 = 0;
  memset(&DAT_0a621b60,0,100);
  memset(&DAT_0a620e90,0,100);
  memset(&DAT_0a620f90,0,100);
  memset(&DAT_0a621028,0,100);
  memset(&DAT_0a620ef8,0,100);
  uVar3 = FUN_0055fc00(&DAT_0058c616);
  sprintf((char *)&local_158,"[%s]",uVar3);
  pcVar7 = (char *)&local_158;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  if ((uint)((int)pcVar7 - ((int)&local_158 + 1)) < 3) {
    local_158 = DAT_005b7b00;
    local_150 = DAT_005b7b08;
  }
  local_560 = 0;
  while( true ) {
    memset(&local_5d8,0,100);
    memset(&local_f0,0,100);
    iVar13 = 0;
    iVar4 = rand();
    iVar4 = iVar4 % 3;
    do {
      iVar5 = rand();
      iVar5 = iVar5 % 3;
      iVar13 = iVar13 + 1;
      if (iVar13 == 10) {
        iVar4 = -1;
      }
    } while (iVar5 == iVar4);
    if (iVar5 == 0) {
      uVar14 = FUN_004911e0(param_3,param_4,1,param_6,0x3c);
      uVar12 = (uint)uVar14;
      local_55c = (uint)((ulonglong)uVar14 >> 0x20);
      DAT_0a621b60 = s_in_a_cave_005b7b0c[0];
      DAT_0a621b60_1._0_1_ = s_in_a_cave_005b7b0c[1];
      DAT_0a621b60_1._1_1_ = s_in_a_cave_005b7b0c[2];
      DAT_0a621b60_1._2_1_ = s_in_a_cave_005b7b0c[3];
      DAT_0a621b60_1._3_1_ = s_in_a_cave_005b7b0c[4];
      DAT_0a621b60_1._4_1_ = s_in_a_cave_005b7b0c[5];
      DAT_0a621b60_1._5_1_ = s_in_a_cave_005b7b0c[6];
      DAT_0a621b60_1._6_1_ = s_in_a_cave_005b7b0c[7];
      DAT_0a621b68 = s_in_a_cave_005b7b0c[8];
      DAT_0a621b68_1 = s_in_a_cave_005b7b0c[9];
      puVar2 = (undefined4 *)&uStack_f1;
      do {
        puVar8 = puVar2;
        puVar2 = (undefined4 *)((int)puVar8 + 1);
      } while (*(char *)((int)puVar8 + 1) != '\0');
      *(undefined4 *)((int)puVar8 + 1) = DAT_005b7b18;
      *(undefined4 *)((int)puVar8 + 5) = DAT_005b7b1c;
      local_20._0_5_ = CONCAT14(DAT_005b52fc,DAT_005b52f8);
    }
    else if (iVar5 == 1) {
      uVar14 = FUN_004911e0(param_3,param_4,1,param_6,0x5d);
      uVar12 = (uint)uVar14;
      DAT_0a621b68 = s_on_a_cliff_005b7b20[8];
      DAT_0a621b68_1 = s_on_a_cliff_005b7b20[9];
      DAT_0a621b6a = s_on_a_cliff_005b7b20[10];
      local_5d8 = DAT_005a9b14;
      local_5d4 = DAT_005a9b18;
      local_55c = (uint)((ulonglong)uVar14 >> 0x20);
      DAT_0a621b60 = s_on_a_cliff_005b7b20[0];
      DAT_0a621b60_1._0_1_ = s_on_a_cliff_005b7b20[1];
      DAT_0a621b60_1._1_1_ = s_on_a_cliff_005b7b20[2];
      DAT_0a621b60_1._2_1_ = s_on_a_cliff_005b7b20[3];
      DAT_0a621b60_1._3_1_ = s_on_a_cliff_005b7b20[4];
      DAT_0a621b60_1._4_1_ = s_on_a_cliff_005b7b20[5];
      DAT_0a621b60_1._5_1_ = s_on_a_cliff_005b7b20[6];
      DAT_0a621b60_1._6_1_ = s_on_a_cliff_005b7b20[7];
      local_20._0_6_ = CONCAT24(s_cliff_0058dde0._4_2_,s_cliff_0058dde0._0_4_);
    }
    else {
      uVar14 = FUN_004911e0(param_3,param_4,5,param_6,0);
      uVar12 = (uint)uVar14;
      local_55c = (uint)((ulonglong)uVar14 >> 0x20);
      if (uVar12 != 0) {
        pcVar7 = (char *)FUN_004076c0();
        pcVar7 = Lowercase(pcVar7);
        sprintf(&DAT_0a621b60,"on a small %s island",pcVar7);
        local_5d8 = DAT_005a9b1c;
        local_5d4 = CONCAT22(local_5d4._2_2_,DAT_005a9b20);
        local_e8[0] = s__triboulder__005a9b04[8];
        local_e8[1] = s__triboulder__005a9b04[9];
        local_e8[2] = s__triboulder__005a9b04[10];
        local_e8[3] = s__triboulder__005a9b04[0xb];
        local_f0._0_1_ = s__triboulder__005a9b04[0];
        local_f0._1_1_ = s__triboulder__005a9b04[1];
        local_f0._2_1_ = s__triboulder__005a9b04[2];
        local_f0._3_1_ = s__triboulder__005a9b04[3];
        local_f0._4_1_ = s__triboulder__005a9b04[4];
        local_f0._5_1_ = s__triboulder__005a9b04[5];
        local_f0._6_1_ = s__triboulder__005a9b04[6];
        local_f0._7_1_ = s__triboulder__005a9b04[7];
        local_e4 = s__triboulder__005a9b04[0xc];
      }
      uVar14 = local_20;
      local_20._0_6_ = CONCAT24(s_island_005b7b44._4_2_,s_island_005b7b44._0_4_);
      local_20._7_1_ = SUB81(uVar14,7);
      local_20._0_7_ = CONCAT16(s_island_005b7b44[6],(undefined6)local_20);
    }
    if (uVar12 != 0) break;
    local_560 = local_560 + 1;
    if (4 < (int)local_560) goto LAB_00548b12;
  }
  pcVar7 = (char *)&local_f0;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  uVar10 = (int)pcVar7 - (int)&local_f0;
  pcVar7 = &cStack_89;
  do {
    pcVar6 = pcVar7 + 1;
    pcVar7 = pcVar7 + 1;
  } while (*pcVar6 != '\0');
  pcVar6 = (char *)&local_f0;
  for (uVar9 = uVar10 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar10 = uVar10 & 3; pcVar11 = (char *)&local_5d8, uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  do {
    cVar1 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  uVar10 = (int)pcVar11 - (int)&local_5d8;
  pcVar7 = &cStack_89;
  do {
    pcVar6 = pcVar7 + 1;
    pcVar7 = pcVar7 + 1;
  } while (*pcVar6 != '\0');
  pcVar6 = (char *)&local_5d8;
  for (uVar9 = uVar10 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar10 = uVar10 & 3; pcVar11 = (char *)&local_158, uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  do {
    cVar1 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  uVar10 = (int)pcVar11 - (int)&local_158;
  pcVar7 = &cStack_89;
  do {
    pcVar6 = pcVar7 + 1;
    pcVar7 = pcVar7 + 1;
  } while (*pcVar6 != '\0');
  pcVar6 = (char *)&local_158;
  for (uVar9 = uVar10 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  DAT_0a620ea8 = s_hidden_somewhere_around_there_005b7b4c[0x18];
  DAT_0a620ea8_1._0_1_ = s_hidden_somewhere_around_there_005b7b4c[0x19];
  DAT_0a620ea8_1._1_1_ = s_hidden_somewhere_around_there_005b7b4c[0x1a];
  DAT_0a620ea8_1._2_1_ = s_hidden_somewhere_around_there_005b7b4c[0x1b];
  DAT_0a620eac = s_hidden_somewhere_around_there_005b7b4c[0x1c];
  DAT_0a620eac_1 = s_hidden_somewhere_around_there_005b7b4c[0x1d];
  DAT_0a620e90 = s_hidden_somewhere_around_there_005b7b4c[0];
  DAT_0a620e90_1._0_1_ = s_hidden_somewhere_around_there_005b7b4c[1];
  DAT_0a620e90_1._1_1_ = s_hidden_somewhere_around_there_005b7b4c[2];
  DAT_0a620e90_1._2_1_ = s_hidden_somewhere_around_there_005b7b4c[3];
  uRam0a620e94._0_1_ = s_hidden_somewhere_around_there_005b7b4c[4];
  uRam0a620e94._1_1_ = s_hidden_somewhere_around_there_005b7b4c[5];
  uRam0a620e94._2_1_ = s_hidden_somewhere_around_there_005b7b4c[6];
  uRam0a620e94._3_1_ = s_hidden_somewhere_around_there_005b7b4c[7];
  uRam0a620e98._0_1_ = s_hidden_somewhere_around_there_005b7b4c[8];
  uRam0a620e98._1_1_ = s_hidden_somewhere_around_there_005b7b4c[9];
  uRam0a620e98._2_1_ = s_hidden_somewhere_around_there_005b7b4c[10];
  uRam0a620e98._3_1_ = s_hidden_somewhere_around_there_005b7b4c[0xb];
  uRam0a620e9c._0_1_ = s_hidden_somewhere_around_there_005b7b4c[0xc];
  uRam0a620e9c._1_1_ = s_hidden_somewhere_around_there_005b7b4c[0xd];
  uRam0a620e9c._2_1_ = s_hidden_somewhere_around_there_005b7b4c[0xe];
  uRam0a620e9c._3_1_ = s_hidden_somewhere_around_there_005b7b4c[0xf];
  for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  DAT_0a620ea0 = s_hidden_somewhere_around_there_005b7b4c[0x10];
  DAT_0a620ea0_1._0_1_ = s_hidden_somewhere_around_there_005b7b4c[0x11];
  DAT_0a620ea2 = s_hidden_somewhere_around_there_005b7b4c[0x12];
  DAT_0a620ea0_1._2_1_ = s_hidden_somewhere_around_there_005b7b4c[0x13];
  DAT_0a620ea4 = s_hidden_somewhere_around_there_005b7b4c[0x14];
  DAT_0a620ea0_1._4_1_ = s_hidden_somewhere_around_there_005b7b4c[0x15];
  DAT_0a620ea0_1._5_1_ = s_hidden_somewhere_around_there_005b7b4c[0x16];
  DAT_0a620ea0_1._6_1_ = s_hidden_somewhere_around_there_005b7b4c[0x17];
  pcVar7 = strstr(local_88,"[cave]");
  if (pcVar7 != (char *)0x0) {
    DAT_0a620e90 = s_hidden_in_the_cave_005b7b6c[0];
    DAT_0a620e90_1._0_1_ = s_hidden_in_the_cave_005b7b6c[1];
    DAT_0a620e90_1._1_1_ = s_hidden_in_the_cave_005b7b6c[2];
    DAT_0a620e90_1._2_1_ = s_hidden_in_the_cave_005b7b6c[3];
    uRam0a620e94._0_1_ = s_hidden_in_the_cave_005b7b6c[4];
    uRam0a620e94._1_1_ = s_hidden_in_the_cave_005b7b6c[5];
    uRam0a620e94._2_1_ = s_hidden_in_the_cave_005b7b6c[6];
    uRam0a620e94._3_1_ = s_hidden_in_the_cave_005b7b6c[7];
    uRam0a620e98._0_1_ = s_hidden_in_the_cave_005b7b6c[8];
    uRam0a620e98._1_1_ = s_hidden_in_the_cave_005b7b6c[9];
    uRam0a620e98._2_1_ = s_hidden_in_the_cave_005b7b6c[10];
    uRam0a620e98._3_1_ = s_hidden_in_the_cave_005b7b6c[0xb];
    uRam0a620e9c._0_1_ = s_hidden_in_the_cave_005b7b6c[0xc];
    uRam0a620e9c._1_1_ = s_hidden_in_the_cave_005b7b6c[0xd];
    uRam0a620e9c._2_1_ = s_hidden_in_the_cave_005b7b6c[0xe];
    uRam0a620e9c._3_1_ = s_hidden_in_the_cave_005b7b6c[0xf];
    DAT_0a620ea2 = s_hidden_in_the_cave_005b7b6c[0x12];
    DAT_0a620ea0 = s_hidden_in_the_cave_005b7b6c[0x10];
    DAT_0a620ea0_1._0_1_ = s_hidden_in_the_cave_005b7b6c[0x11];
  }
  pcVar7 = strstr(local_88,"[pit]");
  if (pcVar7 != (char *)0x0) {
    DAT_0a620e90 = s_buried_in_the_ground_005b7b80[0];
    DAT_0a620e90_1._0_1_ = s_buried_in_the_ground_005b7b80[1];
    DAT_0a620e90_1._1_1_ = s_buried_in_the_ground_005b7b80[2];
    DAT_0a620e90_1._2_1_ = s_buried_in_the_ground_005b7b80[3];
    uRam0a620e94._0_1_ = s_buried_in_the_ground_005b7b80[4];
    uRam0a620e94._1_1_ = s_buried_in_the_ground_005b7b80[5];
    uRam0a620e94._2_1_ = s_buried_in_the_ground_005b7b80[6];
    uRam0a620e94._3_1_ = s_buried_in_the_ground_005b7b80[7];
    uRam0a620e98._0_1_ = s_buried_in_the_ground_005b7b80[8];
    uRam0a620e98._1_1_ = s_buried_in_the_ground_005b7b80[9];
    uRam0a620e98._2_1_ = s_buried_in_the_ground_005b7b80[10];
    uRam0a620e98._3_1_ = s_buried_in_the_ground_005b7b80[0xb];
    uRam0a620e9c._0_1_ = s_buried_in_the_ground_005b7b80[0xc];
    uRam0a620e9c._1_1_ = s_buried_in_the_ground_005b7b80[0xd];
    uRam0a620e9c._2_1_ = s_buried_in_the_ground_005b7b80[0xe];
    uRam0a620e9c._3_1_ = s_buried_in_the_ground_005b7b80[0xf];
    DAT_0a620ea4 = s_buried_in_the_ground_005b7b80[0x14];
    DAT_0a620ea0 = s_buried_in_the_ground_005b7b80[0x10];
    DAT_0a620ea0_1._0_1_ = s_buried_in_the_ground_005b7b80[0x11];
    DAT_0a620ea2 = s_buried_in_the_ground_005b7b80[0x12];
    DAT_0a620ea0_1._2_1_ = s_buried_in_the_ground_005b7b80[0x13];
  }
  pcVar7 = strstr(local_88,"[cave]");
  if (pcVar7 != (char *)0x0) {
    DAT_0a620fa0 = s_somewhere_inside_there_005b7b98[0x10];
    DAT_0a620fa0_1._0_1_ = s_somewhere_inside_there_005b7b98[0x11];
    DAT_0a620fa0_1._1_1_ = s_somewhere_inside_there_005b7b98[0x12];
    DAT_0a620fa0_1._2_1_ = s_somewhere_inside_there_005b7b98[0x13];
    DAT_0a620f90 = s_somewhere_inside_there_005b7b98[0];
    DAT_0a620f90_1._0_1_ = s_somewhere_inside_there_005b7b98[1];
    DAT_0a620f90_1._1_1_ = s_somewhere_inside_there_005b7b98[2];
    DAT_0a620f90_1._2_1_ = s_somewhere_inside_there_005b7b98[3];
    uRam0a620f94._0_1_ = s_somewhere_inside_there_005b7b98[4];
    uRam0a620f94._1_1_ = s_somewhere_inside_there_005b7b98[5];
    uRam0a620f94._2_1_ = s_somewhere_inside_there_005b7b98[6];
    uRam0a620f94._3_1_ = s_somewhere_inside_there_005b7b98[7];
    uRam0a620f98._0_1_ = s_somewhere_inside_there_005b7b98[8];
    uRam0a620f98._1_1_ = s_somewhere_inside_there_005b7b98[9];
    uRam0a620f98._2_1_ = s_somewhere_inside_there_005b7b98[10];
    uRam0a620f98._3_1_ = s_somewhere_inside_there_005b7b98[0xb];
    uRam0a620f9c._0_1_ = s_somewhere_inside_there_005b7b98[0xc];
    uRam0a620f9c._1_1_ = s_somewhere_inside_there_005b7b98[0xd];
    uRam0a620f9c._2_1_ = s_somewhere_inside_there_005b7b98[0xe];
    uRam0a620f9c._3_1_ = s_somewhere_inside_there_005b7b98[0xf];
    DAT_0a620fa6 = s_somewhere_inside_there_005b7b98[0x16];
    DAT_0a620fa4 = s_somewhere_inside_there_005b7b98[0x14];
    DAT_0a620fa4_1._0_1_ = s_somewhere_inside_there_005b7b98[0x15];
  }
  pcVar7 = strstr(local_88,"[triboulder]");
  if (pcVar7 != (char *)0x0) {
    DAT_0a620fc8 = s_in_the_center_of_three_adjacent_b_005b7bb0[0x38];
    DAT_0a620fc8_1._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x39];
    DAT_0a620fc8_1._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x3a];
    DAT_0a620fc8_1._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x3b];
    DAT_0a620f90 = s_in_the_center_of_three_adjacent_b_005b7bb0[0];
    DAT_0a620f90_1._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[1];
    DAT_0a620f90_1._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[2];
    DAT_0a620f90_1._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[3];
    uRam0a620f94._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[4];
    uRam0a620f94._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[5];
    uRam0a620f94._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[6];
    uRam0a620f94._3_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[7];
    uRam0a620f98._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[8];
    uRam0a620f98._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[9];
    uRam0a620f98._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[10];
    uRam0a620f98._3_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0xb];
    uRam0a620f9c._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0xc];
    uRam0a620f9c._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0xd];
    uRam0a620f9c._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0xe];
    uRam0a620f9c._3_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0xf];
    DAT_0a620fa0 = s_in_the_center_of_three_adjacent_b_005b7bb0[0x10];
    DAT_0a620fa0_1._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x11];
    DAT_0a620fa0_1._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x12];
    DAT_0a620fa0_1._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x13];
    DAT_0a620fa4 = s_in_the_center_of_three_adjacent_b_005b7bb0[0x14];
    DAT_0a620fa4_1._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x15];
    DAT_0a620fa6 = s_in_the_center_of_three_adjacent_b_005b7bb0[0x16];
    DAT_0a620fa4_1._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x17];
    uRam0a620fa8._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x18];
    uRam0a620fa8._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x19];
    uRam0a620fa8._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x1a];
    uRam0a620fa8._3_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x1b];
    uRam0a620fac._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x1c];
    uRam0a620fac._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x1d];
    uRam0a620fac._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x1e];
    uRam0a620fac._3_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x1f];
    DAT_0a620fb0 = s_in_the_center_of_three_adjacent_b_005b7bb0[0x20];
    DAT_0a620fb0_1._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x21];
    DAT_0a620fb0_1._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x22];
    DAT_0a620fb0_1._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x23];
    uRam0a620fb4._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x24];
    uRam0a620fb4._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x25];
    uRam0a620fb4._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x26];
    uRam0a620fb4._3_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x27];
    uRam0a620fb8._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x28];
    uRam0a620fb8._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x29];
    uRam0a620fb8._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x2a];
    uRam0a620fb8._3_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x2b];
    uRam0a620fbc._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x2c];
    uRam0a620fbc._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x2d];
    uRam0a620fbc._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x2e];
    uRam0a620fbc._3_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x2f];
    DAT_0a620fc0 = s_in_the_center_of_three_adjacent_b_005b7bb0[0x30];
    DAT_0a620fc0_1._0_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x31];
    DAT_0a620fc0_1._1_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x32];
    DAT_0a620fc0_1._2_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x33];
    DAT_0a620fc0_1._3_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x34];
    DAT_0a620fc0_1._4_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x35];
    DAT_0a620fc0_1._5_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x36];
    DAT_0a620fc0_1._6_1_ = s_in_the_center_of_three_adjacent_b_005b7bb0[0x37];
  }
  pcVar7 = strstr(local_88,"[chasm]");
  uVar10 = local_55c;
  if (pcVar7 != (char *)0x0) {
    pcVar7 = (char *)FUN_004076c0();
    pcVar7 = Lowercase(pcVar7);
    sprintf(&DAT_0a620f90,"within a deep chasm in the %s",pcVar7);
  }
  pcVar7 = (char *)FUN_0055fc00(&DAT_005b7c0c);
  local_560 = atoi(pcVar7);
  iVar4 = extraout_ECX;
  uVar9 = local_560;
  if (local_560 == 0xff) {
    if ((uVar12 < 0xc00) && (uVar10 < 0x800)) {
      iVar4 = ((int)uVar10 >> 5) * 0x60;
      uVar9 = (uint)(byte)(&DAT_02182200)[((int)uVar12 >> 5) + iVar4];
    }
    else {
      uVar9 = 0;
    }
  }
  FUN_0042ea10(iVar4,0);
  FUN_004eba80();
  iVar4 = FUN_004f32d0();
  if (iVar4 != 0) {
    FUN_004ecde0(1);
    DAT_0a620f00 = s_casual_wealth_005b7c18[8];
    DAT_0a620f00_1._0_1_ = s_casual_wealth_005b7c18[9];
    DAT_0a620f00_1._1_1_ = s_casual_wealth_005b7c18[10];
    DAT_0a620f00_1._2_1_ = s_casual_wealth_005b7c18[0xb];
    DAT_0a620f04 = s_casual_wealth_005b7c18[0xc];
    DAT_0a620f04_1 = s_casual_wealth_005b7c18[0xd];
    DAT_0a620ef8 = s_casual_wealth_005b7c18[0];
    DAT_0a620ef9._0_1_ = s_casual_wealth_005b7c18[1];
    DAT_0a620ef9._1_1_ = s_casual_wealth_005b7c18[2];
    DAT_0a620ef9._2_1_ = s_casual_wealth_005b7c18[3];
    DAT_0a620ef9._3_1_ = s_casual_wealth_005b7c18[4];
    DAT_0a620efd = s_casual_wealth_005b7c18[5];
    DAT_0a620efe = s_casual_wealth_005b7c18[6];
    DAT_0a620ef8_4._3_1_ = s_casual_wealth_005b7c18[7];
    sprintf(local_558," of %s origin",(&PTR_s_kaumolais_0058e38c)[uVar9]);
    pcVar7 = local_558;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    uVar12 = (int)pcVar7 - (int)local_558;
    pcVar7 = (char *)((int)&DAT_0a620ef4 + 3);
    do {
      pcVar6 = pcVar7 + 1;
      pcVar7 = pcVar7 + 1;
    } while (*pcVar6 != '\0');
    pcVar6 = local_558;
    for (uVar10 = uVar12 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
    if ((int)DAT_0a84b7a8 < 0) {
      DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
    }
    _Dst = &DAT_0a941eb0 + DAT_0a84b7a8 * 0x400;
    memset(_Dst,0,0x400);
    uVar12 = local_55c;
    FUN_004a8f50(1,_Dst);
    sprintf(&DAT_0a621ac8,"treasure of %s %s",_Dst,&local_20);
    pcVar6 = (char *)FUN_0049b040(1);
    pcVar7 = pcVar6;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar7[0xa621027 - (int)pcVar6] = cVar1;
    } while (cVar1 != '\0');
    pcVar7 = local_88;
    iVar4 = local_56c - (int)pcVar7;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar7[iVar4 + -1] = cVar1;
    } while (cVar1 != '\0');
    __security_check_cookie(local_c ^ (uint)&stack0xfffffffc,uVar12);
    return;
  }
LAB_00548b12:
  __security_check_cookie(local_c ^ (uint)&stack0xfffffffc,0);
  return;
}



/* Extracted native producer 00548f30; nested-producers */

void __fastcall FUN_00548f30(undefined1 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  
  memset(param_1,0,0x4b1);
  *param_1 = 0;
  uVar3 = s_somekind_of_reward_005b7c4c._12_4_;
  uVar2 = s_somekind_of_reward_005b7c4c._8_4_;
  uVar1 = s_somekind_of_reward_005b7c4c._4_4_;
  *(undefined4 *)(param_1 + 1) = s_somekind_of_reward_005b7c4c._0_4_;
  *(undefined4 *)(param_1 + 5) = uVar1;
  *(undefined4 *)(param_1 + 9) = uVar2;
  *(undefined4 *)(param_1 + 0xd) = uVar3;
  *(undefined2 *)(param_1 + 0x11) = s_somekind_of_reward_005b7c4c._16_2_;
  param_1[0x13] = s_somekind_of_reward_005b7c4c[0x12];
  uVar3 = s_What_sort_of_reward_is_that__005b7c60._12_4_;
  uVar2 = s_What_sort_of_reward_is_that__005b7c60._8_4_;
  uVar1 = s_What_sort_of_reward_is_that__005b7c60._4_4_;
  *(undefined4 *)(param_1 + 0x65) = s_What_sort_of_reward_is_that__005b7c60._0_4_;
  *(undefined4 *)(param_1 + 0x69) = uVar1;
  *(undefined4 *)(param_1 + 0x6d) = uVar2;
  *(undefined4 *)(param_1 + 0x71) = uVar3;
  *(undefined8 *)(param_1 + 0x75) = s_What_sort_of_reward_is_that__005b7c60._16_8_;
  *(undefined4 *)(param_1 + 0x7d) = s_What_sort_of_reward_is_that__005b7c60._24_4_;
  param_1[0x81] = s_What_sort_of_reward_is_that__005b7c60[0x1c];
  pcVar5 = "I can\'t speak of it beforehand, but you get a reward of some sort if you help me out.";
  puVar6 = (undefined4 *)(param_1 + 0xc9);
  for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    puVar6 = puVar6 + 1;
  }
  *(undefined2 *)puVar6 = *(undefined2 *)pcVar5;
  uVar3 = s_Now_how_about_my_reward__005b7cd8._12_4_;
  uVar2 = s_Now_how_about_my_reward__005b7cd8._8_4_;
  uVar1 = s_Now_how_about_my_reward__005b7cd8._4_4_;
  *(undefined4 *)(param_1 + 0x259) = s_Now_how_about_my_reward__005b7cd8._0_4_;
  *(undefined4 *)(param_1 + 0x25d) = uVar1;
  *(undefined4 *)(param_1 + 0x261) = uVar2;
  *(undefined4 *)(param_1 + 0x265) = uVar3;
  *(undefined8 *)(param_1 + 0x269) = s_Now_how_about_my_reward__005b7cd8._16_8_;
  param_1[0x271] = s_Now_how_about_my_reward__005b7cd8[0x18];
  uVar3 = s_Here_comes_that_reward_of_yours__005b7cf4._12_4_;
  uVar2 = s_Here_comes_that_reward_of_yours__005b7cf4._8_4_;
  uVar1 = s_Here_comes_that_reward_of_yours__005b7cf4._4_4_;
  *(undefined4 *)(param_1 + 0x2bd) = s_Here_comes_that_reward_of_yours__005b7cf4._0_4_;
  *(undefined4 *)(param_1 + 0x2c1) = uVar1;
  *(undefined4 *)(param_1 + 0x2c5) = uVar2;
  *(undefined4 *)(param_1 + 0x2c9) = uVar3;
  uVar3 = s_Here_comes_that_reward_of_yours__005b7cf4._28_4_;
  uVar2 = s_Here_comes_that_reward_of_yours__005b7cf4._24_4_;
  uVar1 = s_Here_comes_that_reward_of_yours__005b7cf4._20_4_;
  *(undefined4 *)(param_1 + 0x2cd) = s_Here_comes_that_reward_of_yours__005b7cf4._16_4_;
  *(undefined4 *)(param_1 + 0x2d1) = uVar1;
  *(undefined4 *)(param_1 + 0x2d5) = uVar2;
  *(undefined4 *)(param_1 + 0x2d9) = uVar3;
  param_1[0x2dd] = s_Here_comes_that_reward_of_yours__005b7cf4[0x20];
  return;
}



/* Extracted native producer 004a8f50; leaf-producers */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004a8f50(int param_1,int param_2,int param_3,int param_4)

{
  char *pcVar1;
  char cVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  char local_154 [299];
  char cStack_29;
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  if (((param_1 < 0xc00 && param_2 < 0x800) && -1 < param_2) && -1 < param_1) {
    uVar3 = *(ushort *)(&DAT_058f1200 + ((param_2 >> 5) * 0x60 + (param_1 >> 5)) * 2);
    if ((uVar3 & 0x8000) == 0) {
      iVar4 = (uVar3 & 0xff) * 0x10;
      if (param_3 == 0) {
        pcVar6 = &DAT_058f6200 + iVar4;
        do {
          cVar2 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar6[(int)(local_28 + (-1 - (int)(&DAT_058f6200 + iVar4)))] = cVar2;
        } while (cVar2 != '\0');
        pcVar6 = &DAT_058f4200 + (uint)(uVar3 >> 8) * 0x10;
        pcVar7 = pcVar6;
        do {
          cVar2 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar2 != '\0');
        uVar8 = (int)pcVar7 - (int)pcVar6;
        pcVar7 = &cStack_29;
        do {
          pcVar1 = pcVar7 + 1;
          pcVar7 = pcVar7 + 1;
        } while (*pcVar1 != '\0');
      }
      else {
        pcVar6 = &DAT_058f0200 + iVar4;
        do {
          cVar2 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar6[(int)(local_28 + (-1 - (int)(&DAT_058f0200 + iVar4)))] = cVar2;
        } while (cVar2 != '\0');
        pcVar6 = &DAT_058f5200 + (uint)(uVar3 >> 8) * 0x10;
        do {
          cVar2 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar6[(int)(local_154 + (-1 - (int)(&DAT_058f5200 + (uint)(uVar3 >> 8) * 0x10)))] = cVar2
          ;
        } while (cVar2 != '\0');
        pcVar6 = local_28;
        do {
          cVar2 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar2 != '\0');
        if (pcVar6[(int)(local_28 + (-1 - (int)(local_28 + 1)))] == '_') {
          pcVar6[(int)(local_28 + (-1 - (int)(local_28 + 1)))] = ' ';
          if (local_154[0] == '_') {
            pcVar6 = local_154 + 1;
            pcVar7 = pcVar6;
            do {
              cVar2 = *pcVar7;
              pcVar7 = pcVar7 + 1;
            } while (cVar2 != '\0');
            uVar8 = (int)pcVar7 - (int)pcVar6;
            pcVar7 = &cStack_29;
            do {
              pcVar1 = pcVar7 + 1;
              pcVar7 = pcVar7 + 1;
            } while (*pcVar1 != '\0');
          }
          else {
            pcVar6 = local_154;
            pcVar7 = pcVar6;
            do {
              cVar2 = *pcVar7;
              pcVar7 = pcVar7 + 1;
            } while (cVar2 != '\0');
            uVar8 = (int)pcVar7 - (int)pcVar6;
            pcVar7 = &cStack_29;
            do {
              pcVar1 = pcVar7 + 1;
              pcVar7 = pcVar7 + 1;
            } while (*pcVar1 != '\0');
          }
        }
        else {
          if (local_154[0] == '_') {
            local_154[0] = ' ';
          }
          pcVar6 = local_154;
          pcVar7 = pcVar6;
          do {
            cVar2 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar2 != '\0');
          uVar8 = (int)pcVar7 - (int)pcVar6;
          pcVar7 = &cStack_29;
          do {
            pcVar1 = pcVar7 + 1;
            pcVar7 = pcVar7 + 1;
          } while (*pcVar1 != '\0');
        }
      }
      for (uVar5 = uVar8 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar7 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      }
      iVar4 = 0;
      do {
        cVar2 = local_28[iVar4];
        (&DAT_058f7200)[iVar4] = cVar2;
        iVar4 = iVar4 + 1;
      } while (cVar2 != '\0');
    }
    else {
      pcVar6 = (char *)(&DAT_058f7220 + (uVar3 & 0x7fff) * 8);
      do {
        cVar2 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar6[0x58f71ff - (int)(&DAT_058f7220 + (uVar3 & 0x7fff) * 8)] = cVar2;
      } while (cVar2 != '\0');
    }
  }
  else {
    _DAT_058f7200 = DAT_00595a1c;
    DAT_058f7202 = DAT_00595a1e;
  }
  pcVar6 = &DAT_058f7200;
  do {
    cVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar6[param_4 + -0x58f7201] = cVar2;
  } while (cVar2 != '\0');
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}



/* Extracted native producer 004e76c0; leaf-producers */

undefined4 * __thiscall FUN_004e76c0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined2 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  char cVar23;
  undefined4 uVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined2 uVar28;
  undefined4 uVar29;
  undefined4 uVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  undefined2 uVar33;
  undefined4 uVar34;
  undefined4 uVar35;
  undefined4 uVar36;
  undefined4 uVar37;
  char cVar38;
  undefined4 uVar39;
  undefined4 uVar40;
  undefined4 uVar41;
  undefined4 uVar42;
  char cVar43;
  undefined4 uVar44;
  undefined4 uVar45;
  undefined4 uVar46;
  undefined4 uVar47;
  undefined4 uVar48;
  undefined4 uVar49;
  undefined4 uVar50;
  undefined4 uVar51;
  undefined4 uVar52;
  undefined4 uVar53;
  undefined4 uVar54;
  undefined4 uVar55;
  undefined4 uVar56;
  undefined4 uVar57;
  undefined4 uVar58;
  undefined4 uVar59;
  undefined4 uVar60;
  undefined4 uVar61;
  undefined4 uVar62;
  undefined4 uVar63;
  undefined4 uVar64;
  undefined4 uVar65;
  undefined4 uVar66;
  undefined4 uVar67;
  undefined4 uVar68;
  undefined4 uVar69;
  undefined4 uVar70;
  char cVar71;
  undefined4 uVar72;
  undefined4 uVar73;
  undefined4 uVar74;
  undefined4 uVar75;
  char cVar76;
  undefined4 uVar77;
  undefined4 uVar78;
  undefined4 uVar79;
  undefined4 uVar80;
  undefined4 uVar81;
  undefined4 uVar82;
  undefined4 uVar83;
  undefined4 uVar84;
  undefined4 uVar85;
  undefined4 uVar86;
  char cVar87;
  undefined4 uVar88;
  undefined4 uVar89;
  undefined4 uVar90;
  undefined4 uVar91;
  undefined4 uVar92;
  undefined4 uVar93;
  undefined4 uVar94;
  undefined4 uVar95;
  undefined4 uVar96;
  undefined4 uVar97;
  undefined4 uVar98;
  undefined4 uVar99;
  undefined4 uVar100;
  undefined2 uVar101;
  undefined4 uVar102;
  undefined4 uVar103;
  undefined4 uVar104;
  undefined4 uVar105;
  undefined4 uVar106;
  undefined4 uVar107;
  undefined4 uVar108;
  undefined4 uVar109;
  undefined4 uVar110;
  undefined4 uVar111;
  undefined4 uVar112;
  undefined4 uVar113;
  undefined4 uVar114;
  undefined4 uVar115;
  undefined2 uVar116;
  int iVar117;
  char *pcVar118;
  char *pcVar119;
  undefined4 *puVar120;
  
  memset(param_2,0,0x830);
  *param_2 = param_1;
  *(undefined2 *)((int)param_2 + 5) = 0;
  *(undefined1 *)(param_2 + 1) = 0x32;
  uVar116 = s_persuading_the_forest_with_a_bre_005a868c._32_2_;
  uVar115 = s_persuading_the_forest_with_a_bre_005a868c._12_4_;
  uVar114 = s_persuading_the_forest_with_a_bre_005a868c._8_4_;
  uVar113 = s_persuading_the_forest_with_a_bre_005a868c._4_4_;
  uVar112 = s_persuading_the_forest_with_a_bre_005a868c._0_4_;
  uVar111 = s_greeting_the_earth_upon_going_to_005a8588._32_4_;
  uVar110 = s_greeting_the_earth_upon_going_to_005a8588._12_4_;
  uVar109 = s_greeting_the_earth_upon_going_to_005a8588._8_4_;
  uVar108 = s_greeting_the_earth_upon_going_to_005a8588._4_4_;
  uVar107 = s_greeting_the_earth_upon_going_to_005a8588._0_4_;
  uVar106 = s_blood_stanching_incantation_005a853c._24_4_;
  uVar105 = s_blood_stanching_incantation_005a853c._12_4_;
  uVar104 = s_blood_stanching_incantation_005a853c._8_4_;
  uVar103 = s_blood_stanching_incantation_005a853c._4_4_;
  uVar102 = s_blood_stanching_incantation_005a853c._0_4_;
  uVar101 = s_general_sacrifice_005a84ac._16_2_;
  uVar100 = s_general_sacrifice_005a84ac._12_4_;
  uVar99 = s_general_sacrifice_005a84ac._8_4_;
  uVar98 = s_general_sacrifice_005a84ac._4_4_;
  uVar97 = s_general_sacrifice_005a84ac._0_4_;
  uVar96 = s_building_a_fire_to_attract_fores_005a8390._12_4_;
  uVar95 = s_building_a_fire_to_attract_fores_005a8390._8_4_;
  uVar94 = s_building_a_fire_to_attract_fores_005a8390._4_4_;
  uVar93 = s_building_a_fire_to_attract_fores_005a8390._0_4_;
  uVar92 = s_releasing_animal_from_the_forest_005a82f0._32_4_;
  uVar91 = s_releasing_animal_from_the_forest_005a82f0._12_4_;
  uVar90 = s_releasing_animal_from_the_forest_005a82f0._8_4_;
  uVar89 = s_releasing_animal_from_the_forest_005a82f0._4_4_;
  uVar88 = s_releasing_animal_from_the_forest_005a82f0._0_4_;
  cVar87 = s_mittens_for_bear_hunting_005a8224[0x18];
  uVar86 = s_mittens_for_bear_hunting_005a8224._12_4_;
  uVar85 = s_mittens_for_bear_hunting_005a8224._8_4_;
  uVar84 = s_mittens_for_bear_hunting_005a8224._4_4_;
  uVar83 = s_mittens_for_bear_hunting_005a8224._0_4_;
  uVar82 = s_bear_trapping_005a818c._8_4_;
  uVar81 = s_carrying_bear_teeth_to_find_hare_005a80c8._40_4_;
  uVar80 = s_carrying_bear_teeth_to_find_hare_005a80c8._12_4_;
  uVar79 = s_carrying_bear_teeth_to_find_hare_005a80c8._8_4_;
  uVar78 = s_carrying_bear_teeth_to_find_hare_005a80c8._4_4_;
  uVar77 = s_carrying_bear_teeth_to_find_hare_005a80c8._0_4_;
  cVar76 = s_setting_snares_for_hares_005a8030[0x18];
  uVar75 = s_setting_snares_for_hares_005a8030._12_4_;
  uVar74 = s_setting_snares_for_hares_005a8030._8_4_;
  uVar73 = s_setting_snares_for_hares_005a8030._4_4_;
  uVar72 = s_setting_snares_for_hares_005a8030._0_4_;
  cVar71 = s_making_foxes_to_come_at_the_bait_005a7fbc[0x20];
  uVar70 = s_making_foxes_to_come_at_the_bait_005a7fbc._12_4_;
  uVar69 = s_making_foxes_to_come_at_the_bait_005a7fbc._8_4_;
  uVar68 = s_making_foxes_to_come_at_the_bait_005a7fbc._4_4_;
  uVar67 = s_making_foxes_to_come_at_the_bait_005a7fbc._0_4_;
  uVar66 = s_fox_trap_favorableness_005a7f2c._16_4_;
  uVar65 = s_fox_trap_favorableness_005a7f2c._12_4_;
  uVar64 = s_fox_trap_favorableness_005a7f2c._8_4_;
  uVar63 = s_fox_trap_favorableness_005a7f2c._4_4_;
  uVar62 = s_fox_trap_favorableness_005a7f2c._0_4_;
  uVar61 = s_loop_snare_preparations_005a7e54._12_4_;
  uVar60 = s_loop_snare_preparations_005a7e54._8_4_;
  uVar59 = s_loop_snare_preparations_005a7e54._4_4_;
  uVar58 = s_loop_snare_preparations_005a7e54._0_4_;
  uVar57 = s_preventing_a_lynx_from_escaping_005a7d54._12_4_;
  uVar56 = s_preventing_a_lynx_from_escaping_005a7d54._8_4_;
  uVar55 = s_preventing_a_lynx_from_escaping_005a7d54._4_4_;
  uVar54 = s_preventing_a_lynx_from_escaping_005a7d54._0_4_;
  uVar53 = s_making_a_squirrel_stay_still_in_a_005a7c94._32_4_;
  uVar52 = s_making_a_squirrel_stay_still_in_a_005a7c94._12_4_;
  uVar51 = s_making_a_squirrel_stay_still_in_a_005a7c94._8_4_;
  uVar50 = s_making_a_squirrel_stay_still_in_a_005a7c94._4_4_;
  uVar49 = s_making_a_squirrel_stay_still_in_a_005a7c94._0_4_;
  uVar48 = s_making_a_bird_thief_to_confess_005a7b70._24_4_;
  uVar47 = s_making_a_bird_thief_to_confess_005a7b70._12_4_;
  uVar46 = s_making_a_bird_thief_to_confess_005a7b70._8_4_;
  uVar45 = s_making_a_bird_thief_to_confess_005a7b70._4_4_;
  uVar44 = s_making_a_bird_thief_to_confess_005a7b70._0_4_;
  cVar43 = s_gaining_fisherman_s_luck_005a7af4[0x18];
  uVar42 = s_gaining_fisherman_s_luck_005a7af4._12_4_;
  uVar41 = s_gaining_fisherman_s_luck_005a7af4._8_4_;
  uVar40 = s_gaining_fisherman_s_luck_005a7af4._4_4_;
  uVar39 = s_gaining_fisherman_s_luck_005a7af4._0_4_;
  cVar38 = s_fisherman_s_springtime_sacrifice_005a79e0[0x20];
  uVar37 = s_fisherman_s_springtime_sacrifice_005a79e0._12_4_;
  uVar36 = s_fisherman_s_springtime_sacrifice_005a79e0._8_4_;
  uVar35 = s_fisherman_s_springtime_sacrifice_005a79e0._4_4_;
  uVar34 = s_fisherman_s_springtime_sacrifice_005a79e0._0_4_;
  uVar33 = s_rod_fisherman_s_sacrifice_005a78f8._24_2_;
  uVar32 = s_rod_fisherman_s_sacrifice_005a78f8._12_4_;
  uVar31 = s_rod_fisherman_s_sacrifice_005a78f8._8_4_;
  uVar30 = s_rod_fisherman_s_sacrifice_005a78f8._4_4_;
  uVar29 = s_rod_fisherman_s_sacrifice_005a78f8._0_4_;
  uVar28 = s_going_rod_fishing_005a786c._16_2_;
  uVar27 = s_going_rod_fishing_005a786c._12_4_;
  uVar26 = s_going_rod_fishing_005a786c._8_4_;
  uVar25 = s_going_rod_fishing_005a786c._4_4_;
  uVar24 = s_going_rod_fishing_005a786c._0_4_;
  cVar23 = s_meeting_the_spirit_of_the_forest_005a7768[0x20];
  uVar22 = s_meeting_the_spirit_of_the_forest_005a7768._12_4_;
  uVar21 = s_meeting_the_spirit_of_the_forest_005a7768._8_4_;
  uVar20 = s_meeting_the_spirit_of_the_forest_005a7768._4_4_;
  uVar19 = s_meeting_the_spirit_of_the_forest_005a7768._0_4_;
  uVar18 = s_meeting_the_water_folk_005a7678._16_4_;
  uVar17 = s_meeting_the_water_folk_005a7678._12_4_;
  uVar16 = s_meeting_the_water_folk_005a7678._8_4_;
  uVar15 = s_meeting_the_water_folk_005a7678._4_4_;
  uVar14 = s_meeting_the_water_folk_005a7678._0_4_;
  uVar13 = s_net_favorableness_005a7618._16_2_;
  uVar12 = s_net_favorableness_005a7618._12_4_;
  uVar11 = s_net_favorableness_005a7618._8_4_;
  uVar10 = s_net_favorableness_005a7618._4_4_;
  uVar9 = s_net_favorableness_005a7618._0_4_;
  uVar8 = s_felling_tree_for_a_punt_005a757c._12_4_;
  uVar7 = s_felling_tree_for_a_punt_005a757c._8_4_;
  uVar6 = s_felling_tree_for_a_punt_005a757c._4_4_;
  uVar5 = s_felling_tree_for_a_punt_005a757c._0_4_;
  uVar4 = s_bear_skull_rite_005a74a0._12_4_;
  uVar3 = s_bear_skull_rite_005a74a0._8_4_;
  uVar2 = s_bear_skull_rite_005a74a0._4_4_;
  uVar1 = s_bear_skull_rite_005a74a0._0_4_;
  switch(param_1) {
  case 9:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar97;
    *(undefined4 *)((int)param_2 + 0x11) = uVar98;
    *(undefined4 *)((int)param_2 + 0x15) = uVar99;
    *(undefined4 *)((int)param_2 + 0x19) = uVar100;
    *(undefined2 *)((int)param_2 + 0x1d) = uVar101;
    *(undefined1 *)((int)param_2 + 6) = 1;
    pcVar118 = 
    "All-round way to sacrifice something in order to please or thank the spirits and otherworldly beings in various occasions."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x1e; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    *(char *)((int)puVar120 + 2) = pcVar118[2];
    return param_2;
  case 10:
    *(undefined2 *)(param_2 + 1) = 0x101;
    *(undefined1 *)((int)param_2 + 7) = 1;
    *(undefined4 *)((int)param_2 + 0xd) = uVar1;
    *(undefined4 *)((int)param_2 + 0x11) = uVar2;
    *(undefined4 *)((int)param_2 + 0x15) = uVar3;
    *(undefined4 *)((int)param_2 + 0x19) = uVar4;
    pcVar118 = 
    "After the bear is brought down its skull eventually needs to be placed to hang in a big lone pine-tree. That completes the hunting and burial ceremony and assures proper circulation of the bear spirit."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x32; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    return param_2;
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
  case 0x29:
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
  case 0x38:
  case 0x39:
  case 0x3a:
  case 0x3b:
  case 0x3d:
  case 0x3e:
  case 0x3f:
  case 0x40:
  case 0x41:
  case 0x42:
  case 0x43:
  case 0x44:
  case 0x45:
  case 0x47:
  case 0x48:
  case 0x49:
  case 0x4a:
  case 0x4b:
  case 0x4c:
  case 0x4d:
  case 0x4e:
  case 0x4f:
  case 0x51:
  case 0x53:
  case 0x54:
  case 0x55:
  case 0x56:
  case 0x57:
  case 0x58:
  case 0x5b:
  case 0x5c:
  case 0x5f:
  case 0x60:
  case 0x61:
  case 0x62:
  case 99:
  case 0x65:
  case 0x66:
  case 0x67:
  case 0x68:
  case 0x69:
  case 0x6a:
  case 0x6b:
  case 0x6c:
  case 0x6d:
  case 0x70:
  case 0x71:
  case 0x72:
  case 0x74:
  case 0x75:
  case 0x76:
  case 0x77:
  case 0x79:
  case 0x7a:
  case 0x7b:
  case 0x7c:
  case 0x7d:
  case 0x7e:
  case 0x7f:
  case 0x80:
  case 0x81:
  case 0x83:
  case 0x84:
  case 0x85:
  case 0x86:
  case 0x88:
  case 0x89:
  case 0x8a:
  case 0x8b:
  case 0x8c:
  case 0x8d:
  case 0x8e:
  case 0x8f:
  case 0x90:
  case 0x91:
  case 0x92:
  case 0x93:
  case 0x94:
  case 0x95:
  case 0x96:
  case 0x97:
  case 0x98:
  case 0x99:
  case 0x9a:
  case 0x9b:
  case 0x9c:
  case 0x9d:
  case 0x9e:
  case 0x9f:
  case 0xa1:
  case 0xa2:
  case 0xa3:
  case 0xa4:
  case 0xa5:
  case 0xa6:
  case 0xa7:
  case 0xa8:
  case 0xa9:
  case 0xaa:
  case 0xab:
  case 0xac:
  case 0xad:
  case 0xae:
  case 0xaf:
  case 0xb0:
  case 0xb1:
  case 0xb2:
  case 0xb3:
  case 0xb5:
  case 0xb6:
  case 0xb7:
  case 0xb8:
  case 0xb9:
  case 0xba:
  case 0xbb:
  case 0xbc:
  case 0xbd:
  case 0xbf:
  case 0xc1:
  case 0xc2:
  case 0xc3:
  case 0xc4:
  case 0xc5:
  case 0xc6:
  case 199:
  case 0xc9:
  case 0xca:
  case 0xcb:
  case 0xcc:
  case 0xcd:
  case 0xce:
  case 0xcf:
  case 0xd0:
  case 0xd1:
  case 0xd2:
  case 0xd3:
  case 0xd4:
  case 0xd5:
  case 0xd6:
  case 0xd7:
  case 0xd8:
  case 0xd9:
  case 0xda:
  case 0xdb:
  case 0xdc:
  case 0xdd:
  case 0xde:
  case 0xdf:
  case 0xe0:
    goto switchD_004e76fd_caseD_b;
  case 0x19:
    *(undefined2 *)(param_2 + 1) = 0x101;
    *(undefined1 *)((int)param_2 + 7) = 1;
    *(undefined4 *)((int)param_2 + 0xd) = uVar93;
    *(undefined4 *)((int)param_2 + 0x11) = uVar94;
    *(undefined4 *)((int)param_2 + 0x15) = uVar95;
    *(undefined4 *)((int)param_2 + 0x19) = uVar96;
    uVar3 = s_building_a_fire_to_attract_fores_005a8390._28_4_;
    uVar2 = s_building_a_fire_to_attract_fores_005a8390._24_4_;
    uVar1 = s_building_a_fire_to_attract_fores_005a8390._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_building_a_fire_to_attract_fores_005a8390._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    *(undefined8 *)((int)param_2 + 0x2d) = s_building_a_fire_to_attract_fores_005a8390._32_8_;
    pcVar118 = 
    "Forest maids are attracted to come at nighttime campfires in remote forests of spruce and moss by lighting the fire with seven spruce twigs in there along with good pile of other firewood. Sleep on the moss by such fire and they may appear."
    ;
    pcVar119 = (char *)((int)param_2 + 0x5d);
    for (iVar117 = 0x3c; iVar117 != 0; iVar117 = iVar117 + -1) {
      *(undefined4 *)pcVar119 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      pcVar119 = pcVar119 + 4;
    }
    *pcVar119 = *pcVar118;
    return param_2;
  case 0x28:
    *(undefined8 *)((int)param_2 + 0xd) = s_bear_trapping_005a818c._0_8_;
    *(undefined4 *)((int)param_2 + 0x15) = uVar82;
    *(undefined2 *)((int)param_2 + 0x19) = s_bear_trapping_005a818c._12_2_;
    *(undefined2 *)(param_2 + 1) = 0x132;
    pcVar118 = 
    "When deadfall trap is made for a bear you should then set the meat bait there completely naked. Then the bear gets in there nicely."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x21; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    return param_2;
  case 0x3c:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar49;
    *(undefined4 *)((int)param_2 + 0x11) = uVar50;
    *(undefined4 *)((int)param_2 + 0x15) = uVar51;
    *(undefined4 *)((int)param_2 + 0x19) = uVar52;
    uVar3 = s_making_a_squirrel_stay_still_in_a_005a7c94._28_4_;
    uVar2 = s_making_a_squirrel_stay_still_in_a_005a7c94._24_4_;
    uVar1 = s_making_a_squirrel_stay_still_in_a_005a7c94._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_making_a_squirrel_stay_still_in_a_005a7c94._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    *(undefined4 *)((int)param_2 + 0x2d) = uVar53;
    *(undefined2 *)((int)param_2 + 0x31) = s_making_a_squirrel_stay_still_in_a_005a7c94._36_2_;
    *(char *)((int)param_2 + 0x33) = s_making_a_squirrel_stay_still_in_a_005a7c94[0x26];
    pcVar118 = 
    "Turn around and kick a tree with your heel and the squirrel will then stay still in there, even if it would have been jumping around a lot earlier."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x25; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    return param_2;
  case 0x46:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar54;
    *(undefined4 *)((int)param_2 + 0x11) = uVar55;
    *(undefined4 *)((int)param_2 + 0x15) = uVar56;
    *(undefined4 *)((int)param_2 + 0x19) = uVar57;
    uVar3 = s_preventing_a_lynx_from_escaping_005a7d54._28_4_;
    uVar2 = s_preventing_a_lynx_from_escaping_005a7d54._24_4_;
    uVar1 = s_preventing_a_lynx_from_escaping_005a7d54._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_preventing_a_lynx_from_escaping_005a7d54._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    pcVar118 = 
    "Have a capercaillie feather with you when chasing a lynx. The feather is then put on lynx tracks from where it first fled, on its very first escaping tracks. This will burden the lynx, making it more quickly fatigued."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x36; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    return param_2;
  case 0x50:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar62;
    *(undefined4 *)((int)param_2 + 0x11) = uVar63;
    *(undefined4 *)((int)param_2 + 0x15) = uVar64;
    *(undefined4 *)((int)param_2 + 0x19) = uVar65;
    *(undefined4 *)((int)param_2 + 0x1d) = uVar66;
    *(undefined2 *)((int)param_2 + 0x21) = s_fox_trap_favorableness_005a7f2c._20_2_;
    *(char *)((int)param_2 + 0x23) = s_fox_trap_favorableness_005a7f2c[0x16];
    pcVar118 = 
    "To make a fox trap favourable leave it laying at doorstep of a building where womenfolk will get to walk over it."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x1c; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    return param_2;
  case 0x52:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar67;
    *(undefined4 *)((int)param_2 + 0x11) = uVar68;
    *(undefined4 *)((int)param_2 + 0x15) = uVar69;
    *(undefined4 *)((int)param_2 + 0x19) = uVar70;
    uVar3 = s_making_foxes_to_come_at_the_bait_005a7fbc._28_4_;
    uVar2 = s_making_foxes_to_come_at_the_bait_005a7fbc._24_4_;
    uVar1 = s_making_foxes_to_come_at_the_bait_005a7fbc._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_making_foxes_to_come_at_the_bait_005a7fbc._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    *(char *)((int)param_2 + 0x2d) = cVar71;
    pcVar118 = "Baiting a fox-trap at your hunting grounds should be done just around sunset.";
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x13; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    return param_2;
  case 0x59:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar58;
    *(undefined4 *)((int)param_2 + 0x11) = uVar59;
    *(undefined4 *)((int)param_2 + 0x15) = uVar60;
    *(undefined4 *)((int)param_2 + 0x19) = uVar61;
    *(undefined8 *)((int)param_2 + 0x1d) = s_loop_snare_preparations_005a7e54._16_8_;
    pcVar118 = 
    "Be it birds or hares you are after, the loop snares you are about to use are made favorable by leaving them in an ant nest for three nights, and only then picked up and set for a catch."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x2e; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    return param_2;
  case 0x5a:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar72;
    *(undefined4 *)((int)param_2 + 0x11) = uVar73;
    *(undefined4 *)((int)param_2 + 0x15) = uVar74;
    *(undefined4 *)((int)param_2 + 0x19) = uVar75;
    *(undefined8 *)((int)param_2 + 0x1d) = s_setting_snares_for_hares_005a8030._16_8_;
    *(char *)((int)param_2 + 0x25) = cVar76;
    pcVar118 = 
    "Loop snares for hares shouldn\'t be set barehanded but you should always wear mittens, and preferably woollen mittens."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x1d; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    return param_2;
  case 0x5d:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar77;
    *(undefined4 *)((int)param_2 + 0x11) = uVar78;
    *(undefined4 *)((int)param_2 + 0x15) = uVar79;
    *(undefined4 *)((int)param_2 + 0x19) = uVar80;
    uVar3 = s_carrying_bear_teeth_to_find_hare_005a80c8._28_4_;
    uVar2 = s_carrying_bear_teeth_to_find_hare_005a80c8._24_4_;
    uVar1 = s_carrying_bear_teeth_to_find_hare_005a80c8._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_carrying_bear_teeth_to_find_hare_005a80c8._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    *(undefined8 *)((int)param_2 + 0x2d) = s_carrying_bear_teeth_to_find_hare_005a80c8._32_8_;
    *(undefined4 *)((int)param_2 + 0x35) = uVar81;
    pcVar118 = 
    "Bear is a great hunter who always finds its prey, and hunters who carry bear teeth with them can come across hares and game birds as they please."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x24; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    return param_2;
  case 0x5e:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar83;
    *(undefined4 *)((int)param_2 + 0x11) = uVar84;
    *(undefined4 *)((int)param_2 + 0x15) = uVar85;
    *(undefined4 *)((int)param_2 + 0x19) = uVar86;
    *(undefined8 *)((int)param_2 + 0x1d) = s_mittens_for_bear_hunting_005a8224._16_8_;
    *(char *)((int)param_2 + 0x25) = cVar87;
    pcVar118 = 
    "Bear hunter\'s mittens shouldn\'t be made of whatever material. It is the dog fur mittens you should wear in order to have your weapons to be effective and cut the bear good."
    ;
    pcVar119 = (char *)((int)param_2 + 0x5d);
    for (iVar117 = 0x2b; iVar117 != 0; iVar117 = iVar117 + -1) {
      *(undefined4 *)pcVar119 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      pcVar119 = pcVar119 + 4;
    }
    *pcVar119 = *pcVar118;
    return param_2;
  case 100:
    *(undefined2 *)(param_2 + 1) = 0x164;
    *(undefined1 *)((int)param_2 + 7) = 1;
    *(undefined4 *)((int)param_2 + 0xd) = uVar5;
    *(undefined4 *)((int)param_2 + 0x11) = uVar6;
    *(undefined4 *)((int)param_2 + 0x15) = uVar7;
    *(undefined4 *)((int)param_2 + 0x19) = uVar8;
    *(undefined8 *)((int)param_2 + 0x1d) = s_felling_tree_for_a_punt_005a757c._16_8_;
    pcVar118 = 
    "The aspen tree for a punt should be felled when it\'s raining. Carving a punt out of such a log makes it good and fortunate one."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x20; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    return param_2;
  case 0x6e:
    *(undefined2 *)(param_2 + 1) = 0x164;
    *(undefined4 *)((int)param_2 + 0xd) = uVar29;
    *(undefined4 *)((int)param_2 + 0x11) = uVar30;
    *(undefined4 *)((int)param_2 + 0x15) = uVar31;
    *(undefined4 *)((int)param_2 + 0x19) = uVar32;
    *(undefined8 *)((int)param_2 + 0x1d) = s_rod_fisherman_s_sacrifice_005a78f8._16_8_;
    *(undefined2 *)((int)param_2 + 0x25) = uVar33;
    pcVar118 = 
    "The very first fish of the spring that you catch with a fishing rod in open water season should be thrown back into the water to please the spirit of the water and assure your future fishing luck."
    ;
    pcVar119 = (char *)((int)param_2 + 0x5d);
    for (iVar117 = 0x31; iVar117 != 0; iVar117 = iVar117 + -1) {
      *(undefined4 *)pcVar119 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      pcVar119 = pcVar119 + 4;
    }
    *pcVar119 = *pcVar118;
    return param_2;
  case 0x6f:
    *(undefined2 *)(param_2 + 1) = 0x164;
    *(undefined4 *)((int)param_2 + 0xd) = uVar34;
    *(undefined4 *)((int)param_2 + 0x11) = uVar35;
    *(undefined4 *)((int)param_2 + 0x15) = uVar36;
    *(undefined4 *)((int)param_2 + 0x19) = uVar37;
    *(undefined1 *)((int)param_2 + 7) = 1;
    uVar3 = s_fisherman_s_springtime_sacrifice_005a79e0._28_4_;
    uVar2 = s_fisherman_s_springtime_sacrifice_005a79e0._24_4_;
    uVar1 = s_fisherman_s_springtime_sacrifice_005a79e0._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_fisherman_s_springtime_sacrifice_005a79e0._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    *(char *)((int)param_2 + 0x2d) = cVar38;
    pcVar118 = 
    "When first fish of the spring are caught out at a lake in open water season, make a fish soup or boil them right after returning on shore. When it\'s cooked, go away from the pot so that the spirit of the water can have the first taste."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x3b; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    return param_2;
  case 0x73:
    *(undefined2 *)(param_2 + 1) = 0x164;
    *(undefined4 *)((int)param_2 + 0xd) = uVar39;
    *(undefined4 *)((int)param_2 + 0x11) = uVar40;
    *(undefined4 *)((int)param_2 + 0x15) = uVar41;
    *(undefined4 *)((int)param_2 + 0x19) = uVar42;
    *(undefined8 *)((int)param_2 + 0x1d) = s_gaining_fisherman_s_luck_005a7af4._16_8_;
    *(char *)((int)param_2 + 0x25) = cVar43;
    pcVar118 = 
    "You get a good catch if you step in the punt backwards and launch it in the water backwards.";
    pcVar119 = (char *)((int)param_2 + 0x5d);
    for (iVar117 = 0x17; iVar117 != 0; iVar117 = iVar117 + -1) {
      *(undefined4 *)pcVar119 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      pcVar119 = pcVar119 + 4;
    }
    *pcVar119 = *pcVar118;
    return param_2;
  case 0x78:
    *(undefined2 *)(param_2 + 1) = 0x164;
    *(undefined4 *)((int)param_2 + 0xd) = uVar9;
    *(undefined4 *)((int)param_2 + 0x11) = uVar10;
    *(undefined4 *)((int)param_2 + 0x15) = uVar11;
    *(undefined4 *)((int)param_2 + 0x19) = uVar12;
    *(undefined2 *)((int)param_2 + 0x1d) = uVar13;
    uVar4 = s_Let_your_sheep_run_over_your_net_005a7630._64_4_;
    uVar3 = s_Let_your_sheep_run_over_your_net_005a7630._12_4_;
    uVar2 = s_Let_your_sheep_run_over_your_net_005a7630._8_4_;
    uVar1 = s_Let_your_sheep_run_over_your_net_005a7630._4_4_;
    *(undefined4 *)((int)param_2 + 0x5d) = s_Let_your_sheep_run_over_your_net_005a7630._0_4_;
    *(undefined4 *)((int)param_2 + 0x61) = uVar1;
    *(undefined4 *)((int)param_2 + 0x65) = uVar2;
    *(undefined4 *)((int)param_2 + 0x69) = uVar3;
    uVar3 = s_Let_your_sheep_run_over_your_net_005a7630._28_4_;
    uVar2 = s_Let_your_sheep_run_over_your_net_005a7630._24_4_;
    uVar1 = s_Let_your_sheep_run_over_your_net_005a7630._20_4_;
    *(undefined4 *)((int)param_2 + 0x6d) = s_Let_your_sheep_run_over_your_net_005a7630._16_4_;
    *(undefined4 *)((int)param_2 + 0x71) = uVar1;
    *(undefined4 *)((int)param_2 + 0x75) = uVar2;
    *(undefined4 *)((int)param_2 + 0x79) = uVar3;
    uVar3 = s_Let_your_sheep_run_over_your_net_005a7630._44_4_;
    uVar2 = s_Let_your_sheep_run_over_your_net_005a7630._40_4_;
    uVar1 = s_Let_your_sheep_run_over_your_net_005a7630._36_4_;
    *(undefined4 *)((int)param_2 + 0x7d) = s_Let_your_sheep_run_over_your_net_005a7630._32_4_;
    *(undefined4 *)((int)param_2 + 0x81) = uVar1;
    *(undefined4 *)((int)param_2 + 0x85) = uVar2;
    *(undefined4 *)((int)param_2 + 0x89) = uVar3;
    uVar3 = s_Let_your_sheep_run_over_your_net_005a7630._60_4_;
    uVar2 = s_Let_your_sheep_run_over_your_net_005a7630._56_4_;
    uVar1 = s_Let_your_sheep_run_over_your_net_005a7630._52_4_;
    *(undefined4 *)((int)param_2 + 0x8d) = s_Let_your_sheep_run_over_your_net_005a7630._48_4_;
    *(undefined4 *)((int)param_2 + 0x91) = uVar1;
    *(undefined4 *)((int)param_2 + 0x95) = uVar2;
    *(undefined4 *)((int)param_2 + 0x99) = uVar3;
    *(undefined4 *)((int)param_2 + 0x9d) = uVar4;
    *(undefined2 *)((int)param_2 + 0xa1) = s_Let_your_sheep_run_over_your_net_005a7630._68_2_;
    return param_2;
  case 0x82:
    *(undefined2 *)(param_2 + 1) = 0x164;
    *(undefined4 *)((int)param_2 + 0xd) = uVar24;
    *(undefined4 *)((int)param_2 + 0x11) = uVar25;
    *(undefined4 *)((int)param_2 + 0x15) = uVar26;
    *(undefined4 *)((int)param_2 + 0x19) = uVar27;
    *(undefined2 *)((int)param_2 + 0x1d) = uVar28;
    pcVar118 = 
    "When going rod fishing you should first throw the fishing rod into the water, and then you have a good fishing luck."
    ;
    pcVar119 = (char *)((int)param_2 + 0x5d);
    for (iVar117 = 0x1d; iVar117 != 0; iVar117 = iVar117 + -1) {
      *(undefined4 *)pcVar119 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      pcVar119 = pcVar119 + 4;
    }
    *pcVar119 = *pcVar118;
    return param_2;
  case 0x87:
    *(undefined2 *)(param_2 + 1) = 0x164;
    *(undefined4 *)((int)param_2 + 0xd) = uVar14;
    *(undefined4 *)((int)param_2 + 0x11) = uVar15;
    *(undefined4 *)((int)param_2 + 0x15) = uVar16;
    *(undefined4 *)((int)param_2 + 0x19) = uVar17;
    *(undefined4 *)((int)param_2 + 0x1d) = uVar18;
    *(undefined2 *)((int)param_2 + 0x21) = s_meeting_the_water_folk_005a7678._20_2_;
    *(char *)((int)param_2 + 0x23) = s_meeting_the_water_folk_005a7678[0x16];
    *(undefined1 *)((int)param_2 + 7) = 1;
    pcVar118 = 
    "To get to see spirits of the water you should go stand naked on a rock in the water at night. It must be a single rock or skerry, completely surrounded by water, and the water folk may gather around it at midnight."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x35; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    *(char *)((int)puVar120 + 2) = pcVar118[2];
    return param_2;
  case 0xa0:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar44;
    *(undefined4 *)((int)param_2 + 0x11) = uVar45;
    *(undefined4 *)((int)param_2 + 0x15) = uVar46;
    *(undefined4 *)((int)param_2 + 0x19) = uVar47;
    *(undefined1 *)((int)param_2 + 7) = 1;
    *(undefined8 *)((int)param_2 + 0x1d) = s_making_a_bird_thief_to_confess_005a7b70._16_8_;
    *(undefined4 *)((int)param_2 + 0x25) = uVar48;
    *(undefined2 *)((int)param_2 + 0x29) = s_making_a_bird_thief_to_confess_005a7b70._28_2_;
    *(char *)((int)param_2 + 0x2b) = s_making_a_bird_thief_to_confess_005a7b70[0x1e];
    pcVar118 = 
    "Bird thief will come confess if you take three feathers that have remained from the stolen bird and throw them into heated sauna stove after the fire has burnt out. You can also throw the feathers into remains of burnt-out fire which was made on base rock."
    ;
    pcVar119 = (char *)((int)param_2 + 0x5d);
    for (iVar117 = 0x40; iVar117 != 0; iVar117 = iVar117 + -1) {
      *(undefined4 *)pcVar119 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      pcVar119 = pcVar119 + 4;
    }
    *pcVar119 = *pcVar118;
    return param_2;
  case 0xb4:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar102;
    *(undefined4 *)((int)param_2 + 0x11) = uVar103;
    *(undefined4 *)((int)param_2 + 0x15) = uVar104;
    *(undefined4 *)((int)param_2 + 0x19) = uVar105;
    *(undefined1 *)((int)param_2 + 6) = 1;
    *(undefined8 *)((int)param_2 + 0x1d) = s_blood_stanching_incantation_005a853c._16_8_;
    uVar4 = s_Incantation_to_stop_the_wounds_f_005a8558._12_4_;
    uVar3 = s_Incantation_to_stop_the_wounds_f_005a8558._8_4_;
    uVar2 = s_Incantation_to_stop_the_wounds_f_005a8558._4_4_;
    uVar1 = s_Incantation_to_stop_the_wounds_f_005a8558._0_4_;
    *(undefined4 *)((int)param_2 + 0x25) = uVar106;
    uVar5 = s_Incantation_to_stop_the_wounds_f_005a8558._40_4_;
    *(undefined4 *)((int)param_2 + 0x5d) = uVar1;
    *(undefined4 *)((int)param_2 + 0x61) = uVar2;
    *(undefined4 *)((int)param_2 + 0x65) = uVar3;
    *(undefined4 *)((int)param_2 + 0x69) = uVar4;
    uVar3 = s_Incantation_to_stop_the_wounds_f_005a8558._28_4_;
    uVar2 = s_Incantation_to_stop_the_wounds_f_005a8558._24_4_;
    uVar1 = s_Incantation_to_stop_the_wounds_f_005a8558._20_4_;
    *(undefined4 *)((int)param_2 + 0x6d) = s_Incantation_to_stop_the_wounds_f_005a8558._16_4_;
    *(undefined4 *)((int)param_2 + 0x71) = uVar1;
    *(undefined4 *)((int)param_2 + 0x75) = uVar2;
    *(undefined4 *)((int)param_2 + 0x79) = uVar3;
    *(undefined8 *)((int)param_2 + 0x7d) = s_Incantation_to_stop_the_wounds_f_005a8558._32_8_;
    *(undefined4 *)((int)param_2 + 0x85) = uVar5;
    *(undefined2 *)((int)param_2 + 0x89) = s_Incantation_to_stop_the_wounds_f_005a8558._44_2_;
    return param_2;
  case 0xbe:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar19;
    *(undefined4 *)((int)param_2 + 0x11) = uVar20;
    *(undefined4 *)((int)param_2 + 0x15) = uVar21;
    *(undefined4 *)((int)param_2 + 0x19) = uVar22;
    *(undefined1 *)((int)param_2 + 7) = 1;
    uVar3 = s_meeting_the_spirit_of_the_forest_005a7768._28_4_;
    uVar2 = s_meeting_the_spirit_of_the_forest_005a7768._24_4_;
    uVar1 = s_meeting_the_spirit_of_the_forest_005a7768._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_meeting_the_spirit_of_the_forest_005a7768._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    *(char *)((int)param_2 + 0x2d) = cVar23;
    pcVar118 = 
    "The spirit of the forest can be met and addressed by sacrificing silver at an ant nest. You do it alone at night, and then wait for the spirit to arrive. Do not fear and he may speak and show himself to you before dawn."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x37; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    return param_2;
  case 0xc0:
    param_2[1] = &DAT_01010132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar112;
    *(undefined4 *)((int)param_2 + 0x11) = uVar113;
    *(undefined4 *)((int)param_2 + 0x15) = uVar114;
    *(undefined4 *)((int)param_2 + 0x19) = uVar115;
    uVar3 = s_persuading_the_forest_with_a_bre_005a868c._28_4_;
    uVar2 = s_persuading_the_forest_with_a_bre_005a868c._24_4_;
    uVar1 = s_persuading_the_forest_with_a_bre_005a868c._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_persuading_the_forest_with_a_bre_005a868c._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    *(undefined2 *)((int)param_2 + 0x2d) = uVar116;
    *(char *)((int)param_2 + 0x2f) = s_persuading_the_forest_with_a_bre_005a868c[0x22];
    pcVar118 = 
    "The forest can be persuaded to not to hide its thingies when going hunting. It is done by carrying a bread with you which is dropped and left at a spruce on a hill or cliff, and then this specific incantation is cast."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x36; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
switchD_004e76fd_caseD_b:
    return param_2;
  case 200:
    *(undefined2 *)(param_2 + 1) = 0x132;
    *(undefined4 *)((int)param_2 + 0xd) = uVar107;
    *(undefined4 *)((int)param_2 + 0x11) = uVar108;
    *(undefined4 *)((int)param_2 + 0x15) = uVar109;
    *(undefined4 *)((int)param_2 + 0x19) = uVar110;
    *(undefined1 *)((int)param_2 + 6) = 1;
    uVar3 = s_greeting_the_earth_upon_going_to_005a8588._28_4_;
    uVar2 = s_greeting_the_earth_upon_going_to_005a8588._24_4_;
    uVar1 = s_greeting_the_earth_upon_going_to_005a8588._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_greeting_the_earth_upon_going_to_005a8588._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    *(undefined4 *)((int)param_2 + 0x2d) = uVar111;
    *(undefined2 *)((int)param_2 + 0x31) = s_greeting_the_earth_upon_going_to_005a8588._36_2_;
    *(char *)((int)param_2 + 0x33) = s_greeting_the_earth_upon_going_to_005a8588[0x26];
    pcVar118 = 
    "Incantation to greet earth dwellers and underground creatures upon sleeping on the ground at unfamiliar terrain. Performed to assure good night sleep and to avoid being harmed by the possibly angered underground folk."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x36; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    return param_2;
  case 0xe1:
    *(undefined2 *)(param_2 + 1) = 0x101;
    *(undefined4 *)((int)param_2 + 0xd) = uVar88;
    *(undefined4 *)((int)param_2 + 0x11) = uVar89;
    *(undefined4 *)((int)param_2 + 0x15) = uVar90;
    *(undefined4 *)((int)param_2 + 0x19) = uVar91;
    *(undefined1 *)((int)param_2 + 7) = 1;
    uVar3 = s_releasing_animal_from_the_forest_005a82f0._28_4_;
    uVar2 = s_releasing_animal_from_the_forest_005a82f0._24_4_;
    uVar1 = s_releasing_animal_from_the_forest_005a82f0._20_4_;
    *(undefined4 *)((int)param_2 + 0x1d) = s_releasing_animal_from_the_forest_005a82f0._16_4_;
    *(undefined4 *)((int)param_2 + 0x21) = uVar1;
    *(undefined4 *)((int)param_2 + 0x25) = uVar2;
    *(undefined4 *)((int)param_2 + 0x29) = uVar3;
    *(undefined4 *)((int)param_2 + 0x2d) = uVar92;
    *(undefined2 *)((int)param_2 + 0x31) = s_releasing_animal_from_the_forest_005a82f0._36_2_;
    *(char *)((int)param_2 + 0x33) = s_releasing_animal_from_the_forest_005a82f0[0x26];
    pcVar118 = 
    "Cut twigs from a living spruce tree and set them burning on the most fresh tracks of the missing animal you can find."
    ;
    puVar120 = (undefined4 *)((int)param_2 + 0x5d);
    for (iVar117 = 0x1d; iVar117 != 0; iVar117 = iVar117 + -1) {
      *puVar120 = *(undefined4 *)pcVar118;
      pcVar118 = pcVar118 + 4;
      puVar120 = puVar120 + 1;
    }
    *(undefined2 *)puVar120 = *(undefined2 *)pcVar118;
    return param_2;
  default:
    return param_2;
  }
}



/* Extracted native producer 0055eb50; leaf-producers */

void __fastcall FUN_0055eb50(undefined4 param_1)

{
  char local_408 [1024];
  uint local_8;
  
  local_8 = DAT_005e200c ^ (uint)&stack0xfffffffc;
  sprintf(local_408,"TIMESPAN_DAY:%d",param_1);
  MessageResource(local_408);
  __security_check_cookie(local_8 ^ (uint)&stack0xfffffffc);
  return;
}


/* Extracted native producer 00455000; inventory-errors */

void __fastcall FUN_00455000(byte *param_1,char param_2)

{
  byte bVar1;
  char *pcVar2;
  byte *pbVar3;
  
  if (param_2 == '\0') {
    FUN_004f6510();
  }
  pbVar3 = param_1;
  do {
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
    pbVar3[0x6f2c2f - (int)param_1] = bVar1;
  } while (bVar1 != 0);
  pcVar2 = strchr("!:?+=>",(uint)*param_1);
  if (pcVar2 != (char *)0x0) {
    pbVar3 = param_1 + 1;
    do {
      bVar1 = *pbVar3;
      pbVar3 = pbVar3 + 1;
      pbVar3[0x6f2c2f - (int)(param_1 + 1)] = bVar1;
    } while (bVar1 != 0);
  }
  return;
}


/* Extracted native producer 00455060; inventory-errors */

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __fastcall
Inventory(int mode,int selected,int x,int y,char *title,char *verb,uint flags,uint mask,int maximum)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  byte bVar4;
  char cVar5;
  short sVar6;
  char cVar7;
  char *pcVar8;
  uint uVar9;
  uint uVar10;
  char *pcVar11;
  char *pcVar12;
  undefined4 uVar13;
  undefined4 *puVar14;
  byte *pbVar15;
  int iVar16;
  int *piVar17;
  byte *pbVar18;
  int iVar19;
  int *piVar20;
  code *pcVar21;
  int iVar22;
  uint *puVar23;
  undefined4 *puVar24;
  bool bVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  undefined8 uVar32;
  undefined4 auStackY_1584 [31];
  undefined4 uStackY_1508;
  char *pcStackY_1504;
  undefined4 uStackY_1500;
  undefined4 uStackY_14fc;
  undefined4 uStackY_14f8;
  char *pcStackY_14f4;
  int iStackY_14f0;
  undefined1 auStack_14cc [3];
  char local_14c9;
  int local_14c8;
  uint local_14c4;
  byte local_14bd;
  uint local_14bc;
  char local_14b5;
  int iStack_14b4;
  char local_14af;
  char local_14ae;
  char local_14ad;
  uint local_14ac;
  uint local_14a8;
  int local_14a4;
  int local_14a0;
  uint local_149c;
  uint local_1498;
  int local_1494;
  char *local_1490;
  int local_148c;
  byte local_1488 [4];
  int local_1484;
  char local_1480;
  byte local_1422;
  short local_1420;
  byte bStack_141b;
  int iStack_1410;
  int iStack_1400;
  undefined4 local_13d8 [25];
  byte bStack_1372;
  byte abStack_1278 [164];
  byte bStack_11d4;
  int aiStack_11c8 [34];
  int iStack_1140;
  undefined4 auStack_1068 [25];
  byte bStack_1002;
  undefined4 local_da8;
  undefined4 uStack_da4;
  undefined4 uStack_da0;
  undefined4 uStack_d9c;
  undefined4 uStack_d98;
  undefined4 uStack_d94;
  undefined4 uStack_d90;
  undefined4 uStack_d8c;
  undefined4 uStack_d88;
  undefined4 uStack_d84;
  undefined4 uStack_d80;
  undefined4 uStack_d7c;
  undefined4 uStack_d40;
  char acStack_d3c [4];
  char acStack_d38 [4];
  char acStack_d34 [4];
  char acStack_d30 [2];
  char cStack_d2e;
  char acStack_940 [1024];
  char acStack_540 [304];
  char acStack_410 [1028];
  uint local_c;
  
  local_c = DAT_005e200c ^ (uint)auStack_14cc;
  iVar19 = 0;
  local_1490 = verb;
  local_14bd = 0;
  local_14af = '\0';
  local_14ae = '\0';
  local_14ad = '\0';
  local_14a0 = 0;
  local_149c = 0;
  local_1494 = 0;
  local_14b5 = '\0';
  DAT_006f78d4 = 0;
  local_14bc = mode;
  memset(&DAT_006eeda8,0,16000);
  memset(&DAT_006f2c30,0,0x400);
  DAT_04b8e0e9 = 0;
  if ((DAT_0a72b054 != '\x04') && (DAT_0a6d0bc4 != -1)) {
    if ((flags & 0x800) != 0) {
      iVar19 = 10;
    }
    local_14ac = (uint)local_14bd;
    if ((flags & 0x100) != 0) {
      local_14ac = 1;
    }
    local_14a4 = iVar19;
    if (local_14bc == 1) {
      FUN_00452e50();
    }
    else if (((local_14bc == 2) && (iVar19 = FUN_00452fb0(), selected == -1)) && (iVar19 == 0)) {
      DAT_0a622a4c = selected;
      memset(&DAT_005e6ac0,0,0x400);
      MessageResource("CARRY_NOTHING");
      FUN_00455000();
      goto LAB_0045523b;
    }
    local_14bd = 0;
    local_14a8 = 0;
    piVar20 = &DAT_006eedb0;
    do {
      if (*piVar20 != 0) {
        uVar32 = FUN_004c0190();
        puVar14 = (undefined4 *)uVar32;
        pbVar15 = local_1488;
        for (iVar19 = 0x2b; sVar6 = local_1420, iVar19 != 0; iVar19 = iVar19 + -1) {
          *(undefined4 *)pbVar15 = *puVar14;
          puVar14 = puVar14 + 1;
          pbVar15 = pbVar15 + 4;
        }
        if (((x == DAT_0a6d1c9c) && (y == DAT_0a72bd40)) &&
           (((int)((ulonglong)uVar32 >> 0x20) == 1 && (local_1488[0] == 9)))) {
          if ((local_1480 == '\r') && (iVar19 = FUN_0049f9d0(), iVar19 != 0)) {
            *(undefined1 *)((int)piVar20 + 0xe) = 1;
          }
        }
        else if (((local_1488[0] == 6) && (local_1480 == '\t')) &&
                ((local_1420 != 0 &&
                 ((((iVar19 = FUN_0040ca70(), iVar19 != -1000 && (iVar19 != -1)) &&
                   (((&DAT_061515dd)[iVar19 * 0x568] & 0x10) != 0)) && (maximum != 0x2be)))))) {
          *(undefined1 *)((int)piVar20 + 0xe) = 1;
          *(undefined1 *)((int)piVar20 + 0x11) = 1;
        }
        if (maximum == 0x1a7) {
          if (local_1480 == '(') {
            *(undefined1 *)((int)piVar20 + 0xe) = 1;
          }
        }
        else if (maximum == 0x1a4) {
          if (((local_1422 & 0x20) == 0) && (iVar19 = FUN_0044bdb0(), iVar19 != 0)) {
            *(undefined1 *)((int)piVar20 + 0xe) = 1;
            *(undefined1 *)(piVar20 + 4) = 1;
          }
        }
        else if ((maximum == 0x1aa) && ((local_1422 & 0xb0) == 0)) {
          *(undefined1 *)((int)piVar20 + 0xe) = 1;
          *(undefined1 *)((int)piVar20 + 0x13) = 1;
          if ((local_1480 == '(') && (sVar6 == 1)) {
            *(undefined1 *)((int)piVar20 + 0xe) = 0;
            *(undefined1 *)((int)piVar20 + 0x13) = 0;
          }
        }
        if ((local_14a8 == 0) || (local_1488[0] == local_14a8)) {
          local_14a8 = (uint)local_1488[0];
        }
        else {
          local_14bd = 1;
        }
        if ((local_1488[0] == 0xc) && (maximum == 0x2be)) {
          *(undefined1 *)(piVar20 + 5) = 1;
        }
        if (((local_1422 & 0x20) != 0) && ((flags & 0x10) != 0)) {
          *(undefined2 *)((int)piVar20 + 0xe) = 0x101;
        }
        if ((((local_1488[0] == 6) && (sVar6 != 0)) && ((flags & 0x20) != 0)) &&
           (local_1484 != 0x138)) {
          *(undefined1 *)((int)piVar20 + 0xe) = 1;
          *(undefined1 *)((int)piVar20 + 0x11) = 1;
        }
        if (mask != 0) {
          if ((int)mask < 0) {
            if ((mask & 1 << (local_1488[0] & 0x1f)) == 0) {
LAB_00455397:
              if (((flags & 0x40) != 0) && (local_1488[0] != mask)) {
                *(undefined1 *)((int)piVar20 + 0xe) = 1;
                *(undefined1 *)((int)piVar20 + 0x12) = 1;
              }
            }
          }
          else if (mask != local_1488[0]) goto LAB_00455397;
        }
      }
      piVar20 = piVar20 + 8;
    } while ((int)piVar20 < 0x6f2c30);
    local_14c9 = '\0';
    DAT_006f78dc = 0;
    _DAT_006f2c2c = 0;
    puVar14 = &DAT_006eeda8;
    puVar24 = &DAT_006f30a8;
    for (iVar19 = 4000; iVar19 != 0; iVar19 = iVar19 + -1) {
      *puVar24 = *puVar14;
      puVar14 = puVar14 + 1;
      puVar24 = puVar24 + 1;
    }
    local_14c8 = 1;
    pcVar8 = s_undefined_005e23f0;
    DAT_006ea934 = 0;
    DAT_006eeba4 = 0;
    pbVar15 = (byte *)title;
    do {
      bVar4 = *pcVar8;
      bVar25 = bVar4 < *pbVar15;
      if (bVar4 != *pbVar15) {
LAB_00455430:
        uVar9 = -(uint)bVar25 | 1;
        goto LAB_00455435;
      }
      if (bVar4 == 0) break;
      bVar4 = pcVar8[1];
      bVar25 = bVar4 < pbVar15[1];
      if (bVar4 != pbVar15[1]) goto LAB_00455430;
      pcVar8 = pcVar8 + 2;
      pbVar15 = pbVar15 + 2;
    } while (bVar4 != 0);
    uVar9 = 0;
LAB_00455435:
    cVar7 = local_14b5;
    if (((uVar9 == 0) && (DAT_006f309c == mask)) && ((flags & 0x80) == 0)) {
      s_undefined_005e23f0[0] = s_undefined_00595af0[0];
      s_undefined_005e23f0[1] = s_undefined_00595af0[1];
      s_undefined_005e23f0[2] = s_undefined_00595af0[2];
      s_undefined_005e23f0[3] = s_undefined_00595af0[3];
      s_undefined_005e23f0[4] = s_undefined_00595af0[4];
      s_undefined_005e23f0[5] = s_undefined_00595af0[5];
      s_undefined_005e23f0[6] = s_undefined_00595af0[6];
      s_undefined_005e23f0[7] = s_undefined_00595af0[7];
      s_undefined_005e23f0[8] = s_undefined_00595af0[8];
      s_undefined_005e23f0[9] = s_undefined_00595af0[9];
      cVar7 = '\x01';
    }
    DAT_005e23e0 = 5;
    DAT_005e2bf0 = 5;
    DAT_005e2bf4 = 0x1d6;
    DAT_005e23ec = 0x208;
    DAT_0a7849ec = 0x18b;
    memset(&DAT_006f2c30,0,0x400);
    puVar14 = &DAT_006f72b0;
    for (iVar19 = 0x6e; iVar19 != 0; iVar19 = iVar19 + -1) {
      *puVar14 = 0xffffffff;
      puVar14 = puVar14 + 1;
    }
    memset(&DAT_006eeba8,0,0x6e);
    _DAT_006f711c = 0;
    local_148c = FUN_004533a0();
    if ((local_148c != 0) || (mask != 0)) {
      if ((char)flags < '\0') {
        iVar19 = __security_check_cookie(local_c ^ (uint)auStack_14cc);
        return iVar19;
      }
      if ((local_148c != 0) || ((flags & 0x40) == 0)) {
        local_1498 = flags & 1;
        bVar25 = local_1498 != 0;
        if (local_148c == 1) {
          local_149c = (uint)((flags & 4) != 0);
        }
        DAT_0659f958 = 1;
        local_14c4 = (uint)bVar25;
        FUN_0050c540();
        local_da8 = _DAT_005ddac0;
        uStack_da4 = _UNK_005ddac4;
        uStack_da0 = _UNK_005ddac8;
        uStack_d9c = _UNK_005ddacc;
        SDL_UpperBlit();
        if (cVar7 != '\0') {
          DAT_006f78dc = DAT_006f78d8;
          DAT_006ea934 = DAT_006f7468;
          if ((&DAT_006eedb0)[(DAT_006f78d8 + DAT_006f7468) * 8] == 0) {
            DAT_006f78dc = 0;
            DAT_006ea934 = 0;
          }
        }
        DAT_065bbcd8 = 0;
        FUN_0050b0f0();
        iVar19 = 1;
        uVar9 = (uint)bVar25;
LAB_004555f0:
        do {
          if (iVar19 != 0) {
            pcVar8 = title;
            do {
              cVar7 = *pcVar8;
              pcVar8 = pcVar8 + 1;
            } while (cVar7 != '\0');
            if (pcVar8 == title + 1) {
              uStack_d40._0_1_ = s_Items_selection_00595b08[0];
              uStack_d40._1_1_ = s_Items_selection_00595b08[1];
              uStack_d40._2_1_ = s_Items_selection_00595b08[2];
              uStack_d40._3_1_ = s_Items_selection_00595b08[3];
              acStack_d3c[0] = s_Items_selection_00595b08[4];
              acStack_d3c[1] = s_Items_selection_00595b08[5];
              acStack_d3c[2] = s_Items_selection_00595b08[6];
              acStack_d3c[3] = s_Items_selection_00595b08[7];
              acStack_d38[0] = s_Items_selection_00595b08[8];
              acStack_d38[1] = s_Items_selection_00595b08[9];
              acStack_d38[2] = s_Items_selection_00595b08[10];
              acStack_d38[3] = s_Items_selection_00595b08[0xb];
              acStack_d34[0] = s_Items_selection_00595b08[0xc];
              acStack_d34[1] = s_Items_selection_00595b08[0xd];
              acStack_d34[2] = s_Items_selection_00595b08[0xe];
              acStack_d34[3] = s_Items_selection_00595b08[0xf];
            }
            else {
              pcVar8 = title;
              do {
                cVar7 = *pcVar8;
                pcVar8 = pcVar8 + 1;
                pcVar8[(int)(&stack0xfffff2bf + -(int)title)] = cVar7;
              } while (cVar7 != '\0');
            }
            iStackY_14f0 = 0x455660;
            FUN_00516270();
            iStackY_14f0 = 0x45568b;
            FUN_00516270();
            uVar10 = local_1498;
            if (local_1498 == 0) {
              acStack_d30[0] = s_Select_an_item_to_00595b2c[0x10];
              acStack_d30[1] = s_Select_an_item_to_00595b2c[0x11];
              cStack_d2e = s_Select_an_item_to_00595b2c[0x12];
              uStack_d40 = s_Select_an_item_to_00595b2c._0_4_;
              acStack_d3c = (char  [4])s_Select_an_item_to_00595b2c._4_4_;
              acStack_d38 = (char  [4])s_Select_an_item_to_00595b2c._8_4_;
              acStack_d34 = (char  [4])s_Select_an_item_to_00595b2c._12_4_;
            }
            else {
              acStack_d30[0] = s_Select_items_to_00595b18[0x10];
              uStack_d40 = s_Select_items_to_00595b18._0_4_;
              acStack_d3c = (char  [4])s_Select_items_to_00595b18._4_4_;
              acStack_d38 = (char  [4])s_Select_items_to_00595b18._8_4_;
              acStack_d34 = (char  [4])s_Select_items_to_00595b18._12_4_;
            }
            iStackY_14f0 = SDL_MapRGB();
            pcStackY_14f4 = (char *)&uStack_d40;
            uStackY_14f8 = 0x45570f;
            FUN_0050e5a0();
            iStackY_14f0 = 0x45572d;
            SDL_MapRGB();
            FUN_0050e5a0();
            iStackY_14f0 = 0x45575d;
            SDL_MapRGB();
            FUN_0050e5a0();
            iStackY_14f0 = 0x455799;
            CreateMenu(0,"",DAT_005e23e0,DAT_005e2bf0,DAT_005e2bf4,DAT_005e23ec,100);
            DAT_06354a9c = 0;
            DAT_06354b8c = 0;
            DAT_06354aa8 = 0;
            if (uVar10 != 0) {
              uVar9 = 1;
            }
            DAT_06354aa0 = 1;
            iVar19 = 0;
            do {
              pcVar8 = &DAT_0058c616 + iVar19;
              (&DAT_06354ac4)[iVar19] = *pcVar8;
              iVar19 = iVar19 + 1;
            } while (*pcVar8 != '\0');
            iVar19 = 0;
            do {
              pcVar8 = &DAT_0058c616 + iVar19;
              (&DAT_06354b28)[iVar19] = *pcVar8;
              iVar19 = iVar19 + 1;
            } while (*pcVar8 != '\0');
            DAT_06354ab4 = 1;
            DAT_06354b90 = 1;
            local_14c4 = uVar9;
            iVar19 = FUN_00454160();
            if (local_1494 < iVar19) {
              local_1494 = iVar19;
            }
          }
          puVar23 = &DAT_0634efd8;
          if ((&DAT_006eedb0)[(DAT_005e2c08 + DAT_006ea934) * 8] == 0) {
            DAT_006ea934 = 0;
          }
          uVar9 = 0;
          while( true ) {
            if ((int)uVar9 < 100) {
              if ((int)uVar9 < 0) {
                uVar10 = 0;
              }
              else {
                uVar10 = *puVar23;
              }
            }
            else {
              uVar10 = 0;
            }
            if ((((uVar10 == DAT_006eec16) || (0x6354a77 < (int)puVar23)) ||
                ((int)puVar23 < 0x634efd8)) || (*puVar23 == 0)) break;
            sprintf(acStack_540,"listposkeywhile #%d viimeinen %d");
            uVar9 = uVar9 + 1;
            puVar23 = puVar23 + 0x3a;
          }
          if ((int)uVar9 < (int)DAT_006ea934) {
            DAT_006ea934 = uVar9;
          }
          if (DAT_006eeba4 == 2) {
            DAT_006ea934 = DAT_005e23e4 - DAT_005e2c08;
LAB_004558d2:
            DAT_006eeba4 = 0;
          }
          else if (DAT_006eeba4 == 1) {
            DAT_006ea934 = 0;
            puVar23 = &DAT_0634efd8;
            while( true ) {
              if ((int)DAT_006ea934 < 100) {
                if ((int)DAT_006ea934 < 0) {
                  uVar9 = 0;
                }
                else {
                  uVar9 = *puVar23;
                }
              }
              else {
                uVar9 = 0;
              }
              if (uVar9 == DAT_006eec16) break;
              DAT_006ea934 = DAT_006ea934 + 1;
              puVar23 = puVar23 + 0x3a;
            }
            goto LAB_004558d2;
          }
          DAT_06354abc = DAT_06354a34;
          DAT_06354ab0 = DAT_006ea934;
          if (local_14c8 != 0) {
            local_14c9 = '\0';
            iVar19 = FUN_00454f90();
            pcVar21 = SDL_MapRGB_exref;
            iVar16 = 0;
            do {
              if ((*(int *)((int)&DAT_006eedb8 + iVar16) != 0) ||
                 (*(int *)((int)&DAT_006f30b8 + iVar16) != 0)) {
                local_14c9 = '\x01';
                break;
              }
              iVar16 = iVar16 + 0x20;
            } while (iVar16 < 16000);
            local_14a0 = iVar19;
            DAT_06354a30 = SDL_MapRGB();
            iStackY_14f0 = 0xab;
            DAT_06354a9c = 0;
            pcStackY_14f4 = (char *)0xab;
            uStackY_14f8 = *(undefined4 *)(DAT_065bbb10 + 4);
            uStackY_14fc = 0x4559b8;
            uStackY_1500 = SDL_MapRGB();
            uStackY_14fc = 0;
            pcStackY_1504 = "Use hotkeys, mouse click or .ENTER to select.";
            uStackY_1508 = 0x4559d7;
            FUN_0050e5a0();
            FUN_00514680();
            if (local_1498 == 0) {
              if (maximum != 0x1a7) goto LAB_00455a83;
              iVar19 = FUN_0043f3d0();
              cVar7 = iVar19 != 1000;
              iVar19 = FUN_0043f3d0();
              if (iVar19 != 1000) {
                cVar7 = cVar7 + '\x01';
              }
              if (cVar7 != '\0') {
                FUN_004cfaf0();
              }
            }
            else {
              FUN_004cfaf0();
              AddMenuRow(0x3d,"");
              if (local_14c9 == '\0') {
                iStackY_14f0 = SDL_MapRGB();
                pcStackY_14f4 = "You can select multiple items here.";
              }
              else {
                FUN_004cfaf0();
                FUN_004d4560();
                iStackY_14f0 = 0x455b26;
                sprintf(acStack_410,"%s.Done - proceed with selected.");
                DAT_06354bb8 = DAT_06354a30;
                DAT_06354dc0 = DAT_06354a9c;
                DAT_06354a30 = SDL_MapRGB();
                iStackY_14f0 = DAT_0a7849ec + 0x1c;
                DAT_06354a9c = 0;
                pcStackY_14f4 = (char *)0x455b83;
                FUN_004cfaf0();
                DAT_06354a30 = DAT_06354bb8;
                DAT_06354a9c = DAT_06354dc0;
                if (local_14a4 == 0) goto LAB_00455a83;
                if (iVar19 < local_14a4) {
                  sprintf(acStack_940,"...or select %d more entries.");
                  iStackY_14f0 = SDL_MapRGB();
                  pcStackY_14f4 = acStack_940;
                }
                else {
                  iStackY_14f0 = SDL_MapRGB();
                  pcStackY_14f4 = "You have selected the maximum number of entries.";
                }
              }
              uStackY_14f8 = 0x455a7d;
              FUN_0050e5a0();
LAB_00455a83:
              if ((maximum == 0x1aa) && (local_14c9 == '\0')) {
                iVar19 = 0;
                do {
                  if (49999 < (int)(&DAT_0a72acd0)[iVar19]) {
                    uVar32 = FUN_004c0190();
                    iVar19 = (int)((ulonglong)uVar32 >> 0x20);
                    puVar14 = (undefined4 *)uVar32;
                    puVar24 = auStack_1068;
                    for (iVar16 = 0x2b; iVar16 != 0; iVar16 = iVar16 + -1) {
                      *puVar24 = *puVar14;
                      puVar14 = puVar14 + 1;
                      puVar24 = puVar24 + 1;
                    }
                    if ((bStack_1002 & 0x80) != 0) {
                      if ((&DAT_0a72acd0)[iVar19] != 0) {
                        FUN_004cfaf0();
                      }
                      break;
                    }
                  }
                  iVar19 = iVar19 + 1;
                } while (iVar19 < 100);
                iVar19 = 0;
                do {
                  if (49999 < (int)(&DAT_0a72acd0)[iVar19]) {
                    uVar32 = FUN_004c0190();
                    iVar19 = (int)((ulonglong)uVar32 >> 0x20);
                    puVar14 = (undefined4 *)uVar32;
                    puVar24 = local_13d8;
                    for (iVar16 = 0x2b; iVar16 != 0; iVar16 = iVar16 + -1) {
                      *puVar24 = *puVar14;
                      puVar14 = puVar14 + 1;
                      puVar24 = puVar24 + 1;
                    }
                    if ((bStack_1372 & 0x10) != 0) {
                      pcVar21 = SDL_MapRGB_exref;
                      if ((&DAT_0a72acd0)[iVar19] != 0) {
                        FUN_004cfaf0();
                        pcVar21 = SDL_MapRGB_exref;
                      }
                      break;
                    }
                  }
                  iVar19 = iVar19 + 1;
                  pcVar21 = SDL_MapRGB_exref;
                } while (iVar19 < 100);
              }
            }
            DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
            if ((int)DAT_0a84b7a8 < 0) {
              DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
            }
            pcVar8 = &DAT_0a941eb0 + DAT_0a84b7a8 * 0x400;
            memset(pcVar8,0,0x400);
            sprintf(pcVar8,"%c");
            sprintf(pcVar8,"%c");
            FUN_004cfaf0();
            DAT_0a84b7a8 = DAT_0a84b7a8 + 1 & 0x800003ff;
            if ((int)DAT_0a84b7a8 < 0) {
              DAT_0a84b7a8 = (DAT_0a84b7a8 - 1 | 0xfffffc00) + 1;
            }
            pcVar8 = &DAT_0a941eb0 + DAT_0a84b7a8 * 0x400;
            iStackY_14f0 = 0x455dd5;
            memset(pcVar8,0,0x400);
            sprintf(pcVar8,"%c");
            sprintf(pcVar8,"%c");
            sprintf((char *)&uStack_d40,"%s.Move");
            FUN_004cfaf0();
            FUN_004cfaf0();
            iStackY_14f0 = 0x1d6;
            pcStackY_14f4 = (char *)0x455e6e;
            FUN_004cfaf0();
            pcStackY_14f4 = (char *)0x455e7d;
            AddMenuRow(1099,"");
            pcStackY_14f4 = (char *)0x455e8c;
            AddMenuRow(0x44a,"");
            pcStackY_14f4 = "ESC.Cancel";
            uStackY_14f8 = 0x1d6;
            uStackY_14fc = 0x455eb0;
            FUN_004cfaf0();
            if (mask == 0) {
              sprintf((char *)&uStack_d40,"Viewing: All items");
            }
            else {
              FUN_00448ad0();
              sprintf((char *)&uStack_d40,"Viewing: %s");
            }
            iStackY_14f0 = 0x208;
            pcStackY_14f4 = (char *)0x1d5;
            uStackY_14f8 = 0x455f1c;
            FUN_00511070();
            pcVar8 = (char *)&uStack_d40;
            do {
              cVar7 = *pcVar8;
              pcVar8 = pcVar8 + 1;
            } while (cVar7 != '\0');
            iStackY_14f0 = 0x455f73;
            (*pcVar21)();
            FUN_0050e5a0();
            FUN_0050e5a0();
            if (mask != 0) {
              sprintf((char *)&uStack_d40,"%c.All types");
              pcVar8 = (char *)&uStack_d40;
              do {
                cVar7 = *pcVar8;
                pcVar8 = pcVar8 + 1;
              } while (cVar7 != '\0');
              FUN_004cfaf0();
            }
            FUN_004cfaf0();
            AddMenuRow(0x2e,"");
          }
          local_14c8 = 1;
          if (local_149c == 0) {
            do {
              if ((int)DAT_06354ab0 < 100) {
                if ((int)DAT_06354ab0 < 0) {
                  iVar19 = 0;
                }
                else {
                  iVar19 = (&DAT_0634efd8)[DAT_06354ab0 * 0x3a];
                }
              }
              else {
                iVar19 = 0;
              }
              DAT_006ea934 = DAT_06354ab0;
              pcVar8 = strchr(s_abcdefghijklmnopqrstuvwxyzABCDEF_005e27f0,iVar19);
              if (pcVar8 != (char *)0x0) {
                pcVar11 = (char *)FUN_00451770();
                pcVar8 = pcVar11;
                do {
                  cVar7 = *pcVar8;
                  pcVar8[(int)&uStack_d40 - (int)pcVar11] = cVar7;
                  pcVar8 = pcVar8 + 1;
                } while (cVar7 != '\0');
                iVar19 = FUN_0043c8a0();
                if (iVar19 == 0) {
                  pcVar8 = (char *)&uStack_d40;
                  cVar7 = '\0';
                  pcVar11 = pcVar8;
                  do {
                    cVar5 = *pcVar11;
                    pcVar11 = pcVar11 + 1;
                  } while (cVar5 != '\0');
                  pcVar11 = pcVar11 + (-1 - ((int)&uStack_d40 + 1));
                  if (0 < (int)pcVar11) {
                    pcVar12 = (char *)((int)&uStack_d40 + (int)(pcVar11 + 1));
                    do {
                      if ((pcVar12[-1] == ' ') && (cVar7 = cVar7 + '\x01', cVar7 == '\x02')) {
                        pcVar8 = pcVar12;
                      }
                      pcVar11 = pcVar11 + -1;
                      pcVar12 = pcVar12 + -1;
                    } while (0 < (int)pcVar11);
                  }
                  pcVar11 = pcVar8;
                  do {
                    cVar7 = *pcVar11;
                    pcVar11[(int)(acStack_940 + -(int)pcVar8)] = cVar7;
                    pcVar11 = pcVar11 + 1;
                  } while (cVar7 != '\0');
                  iVar19 = FUN_0043c8a0();
                  if (iVar19 == 0) {
                    pcVar8 = (char *)&uStack_d40;
                    uVar9 = 0;
                    pcVar11 = pcVar8;
                    do {
                      cVar7 = *pcVar11;
                      pcVar11 = pcVar11 + 1;
                    } while (cVar7 != '\0');
                    if (pcVar11 != (char *)((int)&uStack_d40 + 1)) {
                      do {
                        if (*(char *)((int)&uStack_d40 + uVar9) == ' ') {
                          pcVar8 = (char *)((int)&uStack_d40 + uVar9 + 1);
                        }
                        uVar9 = uVar9 + 1;
                      } while (uVar9 < (uint)((int)pcVar11 - ((int)&uStack_d40 + 1)));
                    }
                    pcVar11 = pcVar8;
                    do {
                      cVar7 = *pcVar11;
                      pcVar11[(int)(acStack_940 + -(int)pcVar8)] = cVar7;
                      pcVar11 = pcVar11 + 1;
                    } while (cVar7 != '\0');
                    iVar19 = FUN_0043c8a0();
                    if (iVar19 != 0) {
                      iVar19 = 0;
                      do {
                        pcVar8 = acStack_940 + iVar19;
                        *(char *)((int)&uStack_d40 + iVar19) = *pcVar8;
                        iVar19 = iVar19 + 1;
                      } while (*pcVar8 != '\0');
                    }
                  }
                  else {
                    iVar19 = 0;
                    do {
                      pcVar8 = acStack_940 + iVar19;
                      *(char *)((int)&uStack_d40 + iVar19) = *pcVar8;
                      iVar19 = iVar19 + 1;
                    } while (*pcVar8 != '\0');
                  }
                }
                FUN_0043ca90();
              }
              local_14bc = FUN_004d1120();
            } while (local_14bc == 0xffffffff);
            if ((int)local_14bc < 100) {
              if (-1 < (int)local_14bc) goto LAB_0045622d;
              iStack_14b4 = 0;
            }
            else {
              iStack_14b4 = 0;
            }
LAB_004563bf:
            if (iStack_14b4 == 0x2b) {
LAB_004565dd:
              piVar20 = &DAT_006eedac;
              iVar19 = local_14a4;
              do {
                if (((((iVar19 == 0) || (local_14a0 < iVar19)) && (iVar16 = piVar20[1], iVar16 != 0)
                     ) && (*(char *)((int)piVar20 + 0x12) == '\0')) &&
                   (((FUN_004c0190(), (char)piVar20[6] == '\0' || (local_14c9 != '\0')) ||
                    (local_14bd == 0)))) {
                  iVar22 = 0;
                  piVar17 = &DAT_006f30b0;
                  if ((flags & 2) == 0) {
                    piVar20[3] = piVar20[2];
                    do {
                      iVar19 = local_14a4;
                      if (((*piVar17 == iVar16) && (*piVar17 != 0)) && (piVar17[-1] == *piVar20)) {
                        (&DAT_006f30b8)[iVar22 * 8] = piVar20[2];
                        break;
                      }
                      piVar17 = piVar17 + 8;
                      iVar22 = iVar22 + 1;
                    } while ((int)piVar17 < 0x6f6f30);
                  }
                  else {
                    piVar20[3] = 1;
                    do {
                      if (((*piVar17 == iVar16) && (*piVar17 != 0)) && (piVar17[-1] == *piVar20)) {
                        (&DAT_006f30b8)[iVar22 * 8] = 1;
                        break;
                      }
                      piVar17 = piVar17 + 8;
                      iVar22 = iVar22 + 1;
                    } while ((int)piVar17 < 0x6f6f30);
                  }
                }
                if (iVar19 != 0) {
                  local_14a0 = FUN_00454f90();
                }
                piVar20 = piVar20 + 8;
              } while ((int)piVar20 < 0x6f2c2c);
              local_14c8 = 1;
              local_14c4 = 1;
              iVar19 = 1;
            }
            else if (iStack_14b4 == 0x2d) {
              if (maximum == 0x1a7) {
                local_14af = '\x01';
                iStack_14b4 = 0x1b;
              }
              piVar20 = &DAT_006eedac;
              do {
                iVar19 = 0;
                piVar20[3] = 0;
                piVar17 = &DAT_006f30b0;
                do {
                  if (((*piVar17 == piVar20[1]) && (*piVar17 != 0)) && (piVar17[-1] == *piVar20)) {
                    (&DAT_006f30b8)[iVar19 * 8] = 0;
                    break;
                  }
                  piVar17 = piVar17 + 8;
                  iVar19 = iVar19 + 1;
                } while ((int)piVar17 < 0x6f6f30);
                piVar20 = piVar20 + 8;
              } while ((int)piVar20 < 0x6f2c2c);
              iVar19 = 1;
              local_14c8 = 1;
            }
            else {
              if (iStack_14b4 != 0x31) goto switchD_004566f2_caseD_432;
              if (maximum == 0x1aa) {
                local_14ae = '\x01';
                iStack_14b4 = 0x1b;
              }
              piVar20 = &DAT_006eedac;
              do {
                iVar19 = 0;
                piVar20[3] = 0;
                piVar17 = &DAT_006f30b0;
                do {
                  if (((*piVar17 == piVar20[1]) && (*piVar17 != 0)) && (piVar17[-1] == *piVar20)) {
                    (&DAT_006f30b8)[iVar19 * 8] = 0;
                    break;
                  }
                  piVar17 = piVar17 + 8;
                  iVar19 = iVar19 + 1;
                } while ((int)piVar17 < 0x6f6f30);
                piVar20 = piVar20 + 8;
              } while ((int)piVar20 < 0x6f2c2c);
              local_14c8 = 1;
              iVar19 = 1;
            }
            goto LAB_00456552;
          }
          local_14bc = 0;
          local_149c = 0;
LAB_0045622d:
          uVar10 = local_14bc;
          iVar16 = (&DAT_0634efd8)[local_14bc * 0x3a];
          iStack_14b4 = iVar16;
          if (iVar16 != 0x2a) {
            if ((iVar16 == 0x2e) || (iVar16 == 0x3fc)) {
              uVar9 = 0;
              piVar20 = &DAT_006f30b0;
              do {
                if (*piVar20 != 0) {
                  uVar32 = FUN_004c0190();
                  uVar9 = (uint)((ulonglong)uVar32 >> 0x20);
                  puVar14 = (undefined4 *)uVar32;
                  pbVar15 = abStack_1278;
                  for (iVar19 = 0x2b; iVar19 != 0; iVar19 = iVar19 + -1) {
                    *(undefined4 *)pbVar15 = *puVar14;
                    puVar14 = puVar14 + 1;
                    pbVar15 = pbVar15 + 4;
                  }
                  if (abStack_1278[0] - 1 < 0xe) {
                    uVar9 = uVar9 | 1 << (abStack_1278[0] & 0x1f);
                  }
                  if ((bStack_11d4 & 3) != 0) {
                    uVar9 = uVar9 | 0x8000000;
                  }
                }
                piVar20 = piVar20 + 8;
              } while ((int)piVar20 < 0x6f6f30);
              local_14a8 = DAT_005e23e0;
              iStackY_14f0 = 0x4569ad;
              local_14bc = uVar9;
              SDL_MapRGB();
              FUN_0050d900();
              uVar9 = FUN_00453130();
              if (uVar9 != 0xffffffff) {
                puVar14 = &DAT_006f30a8;
                puVar24 = &DAT_006eeda8;
                for (iVar19 = 4000; iVar19 != 0; iVar19 = iVar19 + -1) {
                  *puVar24 = *puVar14;
                  puVar14 = puVar14 + 1;
                  puVar24 = puVar24 + 1;
                }
                local_148c = FUN_004533a0();
                DAT_006f78dc = 0;
                DAT_006ea934 = 0;
                mask = uVar9;
              }
              DAT_065bba5c = 1;
              FUN_0050c690();
              FUN_0050c4c0();
              uStack_d98 = _DAT_005ddac0;
              uStack_d94 = _UNK_005ddac4;
              uStack_d90 = _UNK_005ddac8;
              uStack_d8c = _UNK_005ddacc;
              SDL_UpperBlit();
              FUN_0050c540();
              DAT_065bba5c = 0;
              iVar19 = local_14c8;
              uVar9 = local_14c4;
              goto LAB_004555f0;
            }
            if (iVar16 == 0x20) {
              if (local_1498 != 0) {
                FUN_00454f20();
                uVar28 = 0;
                uVar29 = 0;
                uVar30 = 0;
                uVar31 = 0;
                piVar20 = &DAT_006eedf8;
                uVar9 = 0;
                uVar10 = 0;
                uVar26 = 0;
                uVar27 = 0;
                do {
                  piVar2 = piVar20 + 0x28;
                  piVar17 = piVar20 + 0x10;
                  piVar3 = piVar20 + 0x20;
                  uVar28 = uVar28 & -(uint)(piVar20[-0x10] == 0) |
                           ~-(uint)(piVar20[-0x10] == 0) & _DAT_005dd800 + uVar28;
                  uVar29 = uVar29 & -(uint)(piVar20[-8] == 0) |
                           ~-(uint)(piVar20[-8] == 0) & _UNK_005dd804 + uVar29;
                  uVar30 = uVar30 & -(uint)(*piVar20 == 0) |
                           ~-(uint)(*piVar20 == 0) & _UNK_005dd808 + uVar30;
                  uVar31 = uVar31 & -(uint)(piVar20[8] == 0) |
                           ~-(uint)(piVar20[8] == 0) & _UNK_005dd80c + uVar31;
                  piVar1 = piVar20 + 0x18;
                  piVar20 = piVar20 + 0x40;
                  uVar9 = uVar9 & -(uint)(*piVar17 == 0) |
                          ~-(uint)(*piVar17 == 0) & uVar9 + _DAT_005dd800;
                  uVar10 = uVar10 & -(uint)(*piVar1 == 0) |
                           ~-(uint)(*piVar1 == 0) & uVar10 + _UNK_005dd804;
                  uVar26 = uVar26 & -(uint)(*piVar3 == 0) |
                           ~-(uint)(*piVar3 == 0) & uVar26 + _UNK_005dd808;
                  uVar27 = uVar27 & -(uint)(*piVar2 == 0) |
                           ~-(uint)(*piVar2 == 0) & uVar27 + _UNK_005dd80c;
                } while ((int)piVar20 < 0x6f2bf8);
                piVar20 = &DAT_006f2bb8;
                iVar19 = uVar9 + uVar28 + uVar26 + uVar30 + uVar10 + uVar29 + uVar27 + uVar31;
                do {
                  if (*piVar20 != 0) {
                    iVar19 = iVar19 + 1;
                  }
                  piVar20 = piVar20 + 8;
                } while ((int)piVar20 < 0x6f2c38);
                if (iVar19 != 0) {
                  if (DAT_006ea884 == 0) {
                    FUN_0050dad0();
                  }
                  else {
                    SDL_UpperBlit();
                    if (DAT_065bba5c == 0) {
                      FUN_0050af90();
                      if ((DAT_065bbcd8 != 0) && (FUN_00510040(), DAT_065bbcd8 == 2)) {
                        DAT_065bbcd8 = 0;
                      }
                      FUN_0050b3c0();
                      if (DAT_0a5c1c54 == 0) {
                        SDL_RenderPresent();
                        DAT_0659f958 = 0;
                        iVar19 = __security_check_cookie(local_c ^ (uint)auStack_14cc);
                        return iVar19;
                      }
                    }
                  }
                  DAT_0659f958 = 0;
                  iVar19 = __security_check_cookie(local_c ^ (uint)auStack_14cc);
                  return iVar19;
                }
              }
              goto LAB_004563bf;
            }
            if (iVar16 < 0x431) {
              if (iVar16 == 0x430) goto switchD_004566f2_caseD_44a;
              if (iVar16 < 0x33) {
                if (iVar16 != 0x32) goto LAB_004563bf;
                if (maximum == 0x1aa) {
                  local_14ad = '\x02';
                  iStack_14b4 = 0x1b;
                }
                piVar20 = &DAT_006eedac;
                do {
                  iVar19 = 0;
                  piVar20[3] = 0;
                  piVar17 = &DAT_006f30b0;
                  do {
                    if (((*piVar17 == piVar20[1]) && (*piVar17 != 0)) && (piVar17[-1] == *piVar20))
                    {
                      (&DAT_006f30b8)[iVar19 * 8] = 0;
                      break;
                    }
                    piVar17 = piVar17 + 8;
                    iVar19 = iVar19 + 1;
                  } while ((int)piVar17 < 0x6f6f30);
                  piVar20 = piVar20 + 8;
                } while ((int)piVar20 < 0x6f2c2c);
                iVar19 = 1;
                local_14c8 = 1;
                goto LAB_00456552;
              }
              if (iVar16 == 0x3d) goto LAB_004565dd;
              if (iVar16 != 0x423) goto switchD_004566f2_caseD_432;
              FUN_004df7b0();
              goto LAB_00456a7f;
            }
            iVar19 = local_14c8;
            switch(iVar16) {
            case 0x431:
              if (DAT_005e2c08 == 0) {
                DAT_006ea934 = 0;
              }
              else {
                DAT_006f78dc = DAT_006f78dc - local_1494;
                DAT_006ea934 = 0;
                if (DAT_006f78dc < 0) {
                  DAT_006f78dc = 0;
                }
                local_14c8 = 1;
                iVar19 = 1;
              }
              break;
            case 0x438:
            case 1099:
              iVar19 = 1;
              if (iVar16 == 1099) {
                iVar19 = 4;
              }
              if (iVar19 != 0) {
                iVar16 = DAT_005e2c08 + DAT_006ea934;
                uVar9 = DAT_006ea934;
                do {
                  local_14c8 = 0;
                  if (iVar16 < DAT_005e23e4) {
                    uVar9 = uVar9 + 1;
                    iVar16 = iVar16 + 1;
                    DAT_006ea934 = uVar9;
                  }
                  else if ((&DAT_006eedd0)[DAT_005e23e4 * 8] != 0) {
                    DAT_006eeba4 = 2;
                    DAT_006f78dc = DAT_006f78dc + 1;
                    local_14c8 = 1;
                  }
                  iVar19 = iVar19 + -1;
                } while (iVar19 != 0);
              }
            default:
switchD_004566f2_caseD_432:
              iVar19 = local_14c8;
              break;
            case 0x439:
              if ((&DAT_006eedd0)[DAT_005e23e4 * 8] == 0) {
                DAT_006ea934 = DAT_005e23e4 - DAT_005e2c08;
              }
              else {
                DAT_006f78dc = DAT_005e23e4 + 1;
                DAT_006ea934 = 0;
              }
              break;
            case 0x44a:
switchD_004566f2_caseD_44a:
              iVar22 = 1;
              if (iVar16 == 0x44a) {
                iVar22 = 4;
              }
              uVar9 = DAT_006ea934;
              if (iVar22 == 0) goto switchD_004566f2_caseD_432;
              do {
                iVar19 = 0;
                local_14c8 = 0;
                if (uVar9 == 0) {
                  if (0 < DAT_006f78dc) {
                    iVar19 = 1;
                    DAT_006f78dc = DAT_006f78dc + -1;
                    local_14c8 = 1;
                    uVar9 = 0;
                    DAT_006ea934 = uVar9;
                  }
                }
                else {
                  uVar9 = uVar9 - 1;
                  DAT_006ea934 = uVar9;
                }
                iVar22 = iVar22 + -1;
              } while (iVar22 != 0);
            }
LAB_00456552:
            uVar9 = local_14c4;
            pcVar21 = SDL_UpperBlit_exref;
            iVar16 = iStack_14b4;
            uVar10 = local_14bc;
            if (iStack_14b4 == 0x1b) {
              if (DAT_006ea884 == 0) {
                FUN_0050dad0();
                pcVar21 = SDL_UpperBlit_exref;
              }
              else {
                SDL_UpperBlit();
                if (DAT_065bba5c == 0) {
                  FUN_0050af90();
                  if ((DAT_065bbcd8 != 0) && (FUN_00510040(), DAT_065bbcd8 == 2)) {
                    DAT_065bbcd8 = 0;
                  }
                  FUN_0050b3c0();
                  if (DAT_0a5c1c54 == 0) {
                    SDL_RenderPresent();
                  }
                }
              }
              if ((local_14c9 == '\0') || ((flags & 0x400) != 0)) goto LAB_00457573;
              if ((char)local_14ac == '\0') {
                FUN_004f6510();
              }
              iVar16 = 0;
              do {
                cVar7 = "!You have some items selected."[iVar16];
                (&DAT_006f2c30)[iVar16] = cVar7;
                iVar16 = iVar16 + 1;
              } while (cVar7 != '\0');
              pcVar8 = strchr("!:?+=>",0x21);
              if (pcVar8 != (char *)0x0) {
                iVar16 = 0;
                do {
                  cVar7 = "!You have some items selected."[iVar16 + 1];
                  (&DAT_006f2c30)[iVar16] = cVar7;
                  iVar16 = iVar16 + 1;
                } while (cVar7 != '\0');
              }
              cVar7 = FUN_004fbb10();
              if (cVar7 != '\0') goto LAB_00457573;
              DAT_065bbcd8 = 0;
              FUN_0050b0f0();
              local_da8 = _DAT_005ddac0;
              uStack_da4 = _UNK_005ddac4;
              uStack_da0 = _UNK_005ddac8;
              uStack_d9c = _UNK_005ddacc;
              (*pcVar21)();
            }
            else {
LAB_00456a7f:
              iVar19 = 0;
              do {
                pcVar8 = &DAT_006f78e0 + iVar19;
                (&DAT_006eaac8)[iVar19] = *pcVar8;
                iVar19 = iVar19 + 1;
              } while (*pcVar8 != '\0');
              bVar25 = false;
              if ((iVar16 == 0x44a) || (iVar16 == 1099)) {
                bVar25 = true;
              }
              pcVar8 = strchr(s_abcdefghijklmnopqrstuvwxyzABCDEF_005e27f0,iVar16);
              iVar19 = local_14c8;
              uVar9 = local_14c4;
              if (((pcVar8 != (char *)0x0) && (iVar16 != 0)) && (!bVar25)) {
                iVar16 = DAT_005e2c08 + uVar10;
                iVar22 = iVar16 * 0x20;
                DAT_006ea934 = uVar10;
                if ((&DAT_006eedb8)[iVar16 * 8] != 0) {
                  iVar19 = 0;
                  (&DAT_006eedb8)[iVar16 * 8] = 0;
                  piVar20 = &DAT_006f30b0;
                  do {
                    if (((*piVar20 == (&DAT_006eedb0)[iVar16 * 8]) && (*piVar20 != 0)) &&
                       (piVar20[-1] == (&DAT_006eedac)[iVar16 * 8])) {
                      (&DAT_006f30b8)[iVar19 * 8] = 0;
                      break;
                    }
                    piVar20 = piVar20 + 8;
                    iVar19 = iVar19 + 1;
                  } while ((int)piVar20 < 0x6f6f30);
                  goto LAB_004573f0;
                }
                if ((&DAT_006eedbe)[iVar22] != '\0') goto code_r0x00456afb;
                if ((local_14a4 == 0) || (local_14a0 < local_14a4)) {
                  if ((maximum == 0x38e) || (maximum == 900)) {
                    local_14a8 = (&DAT_0634efe0)[uVar10 * 0x3a] + (&DAT_0634efe8)[uVar10 * 0x3a];
                    iStack_14b4 = (&DAT_0634efe4)[uVar10 * 0x3a];
                    puVar14 = (undefined4 *)FUN_004c0190();
                    pbVar15 = local_1488;
                    for (iVar19 = 0x2b; iVar19 != 0; iVar19 = iVar19 + -1) {
                      *(undefined4 *)pbVar15 = *puVar14;
                      puVar14 = puVar14 + 1;
                      pbVar15 = pbVar15 + 4;
                    }
                    switch(local_1484) {
                    case 0x14b:
                    case 0x15f:
                    case 0x162:
                      cVar7 = '\x02';
                      break;
                    default:
                      if (local_1488[0] == 3) {
                        cVar7 = '\x02';
                      }
                      else {
                        cVar7 = iStack_1410 != 0;
                      }
                      break;
                    case 0x15e:
                      cVar7 = '\x01';
                    }
                    if (cVar7 != '\0') {
                      puVar14 = (undefined4 *)FUN_004c0190();
                      puVar24 = auStackY_1584;
                      for (iVar19 = 0x2b; iVar19 != 0; iVar19 = iVar19 + -1) {
                        *puVar24 = *puVar14;
                        puVar14 = puVar14 + 1;
                        puVar24 = puVar24 + 1;
                      }
                      DAT_006f78d4 = FUN_0044fc40();
                      iVar19 = local_14c8;
                      uVar9 = local_14c4;
                      if (DAT_006f78d4 == 0) goto LAB_004555f0;
                    }
                    if (((local_1480 == '\t') && (2 < bStack_141b)) || (local_1484 == 0x14d)) {
                      pbVar15 = local_1488;
                      puVar14 = auStackY_1584;
                      for (iVar19 = 0x2b; iVar19 != 0; iVar19 = iVar19 + -1) {
                        *puVar14 = *(undefined4 *)pbVar15;
                        pbVar15 = pbVar15 + 4;
                        puVar14 = puVar14 + 1;
                      }
                      DAT_006f78d4 = FUN_0044ffc0();
                      iVar19 = local_14c8;
                      uVar9 = local_14c4;
                      if (DAT_006f78d4 == 0) goto LAB_004555f0;
                    }
                    if (local_1484 == 0xf9) {
                      if (iStack_1400 != 0) {
                        piVar20 = (int *)FUN_004c0190();
                        piVar17 = aiStack_11c8;
                        for (iVar19 = 0x2b; iVar19 != 0; iVar19 = iVar19 + -1) {
                          *piVar17 = *piVar20;
                          piVar20 = piVar20 + 1;
                          piVar17 = piVar17 + 1;
                        }
                        if (((aiStack_11c8[1] == 0xf9) && (iStack_1140 == 0)) ||
                           (iVar19 = FUN_0049fb40(), iVar19 == 0)) goto LAB_0045719c;
                      }
                    }
                    else if ((local_1484 == 0x78) && (iStack_1400 != 0)) {
LAB_0045719c:
                      pbVar15 = local_1488;
                      puVar14 = auStackY_1584;
                      for (iVar19 = 0x2b; iVar19 != 0; iVar19 = iVar19 + -1) {
                        *puVar14 = *(undefined4 *)pbVar15;
                        pbVar15 = pbVar15 + 4;
                        puVar14 = puVar14 + 1;
                      }
                      DAT_006f78d4 = FUN_004501a0();
                      iVar19 = local_14c8;
                      uVar9 = local_14c4;
                      if (DAT_006f78d4 == 0) goto LAB_004555f0;
                    }
                  }
                  if ((((int)(&DAT_006eedb4)[iVar16 * 8] < 2) || ((flags & 0x201) == 0)) ||
                     ((flags & 2) != 0)) {
                    iVar19 = 0;
                    (&DAT_006eedb8)[iVar16 * 8] = 1;
                    piVar20 = &DAT_006f30b0;
                    do {
                      if (((*piVar20 == (&DAT_006eedb0)[iVar16 * 8]) && (*piVar20 != 0)) &&
                         (piVar20[-1] == (&DAT_006eedac)[iVar16 * 8])) {
                        (&DAT_006f30b8)[iVar19 * 8] = 1;
                        break;
                      }
                      piVar20 = piVar20 + 8;
                      iVar19 = iVar19 + 1;
                    } while ((int)piVar20 < 0x6f6f30);
                    DAT_006f7468 = DAT_006ea934;
                    DAT_006f78d8 = DAT_006f78dc;
                    DAT_006f309c = mask;
                    pcVar8 = title;
                    do {
                      cVar7 = *pcVar8;
                      pcVar8[(int)s_undefined_005e23f0 - (int)title] = cVar7;
                      pcVar8 = pcVar8 + 1;
                    } while (cVar7 != '\0');
                    goto LAB_004573f0;
                  }
                  SDL_MapRGB();
                  FUN_004d0650();
                  if (((DAT_0634e5dc == 0) && (DAT_06354df4 == 0)) ||
                     (uVar9 = SDL_GetModState(), (uVar9 & 3) == 0)) {
                    uVar13 = FUN_004fbd80();
                    (&DAT_006eedb8)[iVar16 * 8] = uVar13;
                    iVar19 = 0;
                    piVar20 = &DAT_006f30b0;
                    do {
                      if (((*piVar20 == (&DAT_006eedb0)[iVar16 * 8]) && (*piVar20 != 0)) &&
                         (piVar20[-1] == (&DAT_006eedac)[iVar16 * 8])) goto LAB_004572e7;
                      piVar20 = piVar20 + 8;
                      iVar19 = iVar19 + 1;
                    } while ((int)piVar20 < 0x6f6f30);
                  }
                  else {
                    uVar13 = (&DAT_006eedb4)[iVar16 * 8];
                    iVar19 = 0;
                    piVar20 = &DAT_006f30b0;
                    (&DAT_006eedb8)[iVar16 * 8] = uVar13;
                    do {
                      if (((*piVar20 == (&DAT_006eedb0)[iVar16 * 8]) && (*piVar20 != 0)) &&
                         (piVar20[-1] == (&DAT_006eedac)[iVar16 * 8])) goto LAB_004572e7;
                      piVar20 = piVar20 + 8;
                      iVar19 = iVar19 + 1;
                    } while ((int)piVar20 < 0x6f6f30);
                  }
                  goto LAB_004572f0;
                }
              }
            }
            goto LAB_004555f0;
          }
          memcpy(&DAT_006eeda8,&DAT_006f30a8,16000);
          mask = 0;
          FUN_004533a0();
          DAT_006f78dc = 0;
          local_14c8 = 1;
          DAT_006ea934 = 0;
          iVar19 = local_14c8;
          uVar9 = local_14c4;
        } while( true );
      }
    }
    iVar19 = __security_check_cookie(local_c ^ (uint)auStack_14cc);
    return iVar19;
  }
  goto LAB_0045523b;
code_r0x00456afb:
  DAT_065bba5c = 1;
  SDL_UpperBlit();
  if (DAT_065bba5c == 0) {
    FUN_0050af90();
    if ((DAT_065bbcd8 != 0) && (FUN_00510040(), DAT_065bbcd8 == 2)) {
      DAT_065bbcd8 = 0;
    }
    FUN_0050b3c0();
    if (DAT_0a5c1c54 == 0) {
      SDL_RenderPresent();
    }
  }
  DAT_0a62284c = (&DAT_006eedb0)[iVar16 * 8];
  pcVar8 = MessageResource("ITEM_INVALID");
  sprintf((char *)&uStack_d40,pcVar8);
  if (((flags & 0x10) != 0) && ((&DAT_006eedbf)[iVar22] != '\0')) {
    pcVar8 = MessageResource("ITEM_BEING_WORN");
    sprintf((char *)&uStack_d40,pcVar8);
  }
  if (((flags & 0x20) != 0) && ((&DAT_006eedc1)[iVar22] != '\0')) {
    pcVar8 = MessageResource("ITEM_IN_USE");
    sprintf((char *)&uStack_d40,pcVar8);
  }
  if (maximum == 0x1a4) {
    if ((&DAT_006eedc0)[iVar22] == '\0') {
      if ((&DAT_006eedbf)[iVar22] == '\0') {
        if ((char)local_14ac == '\0') {
          FUN_004f6510();
        }
        iVar19 = 0;
        do {
          cVar7 = *(char *)((int)&uStack_d40 + iVar19);
          (&DAT_006f2c30)[iVar19] = cVar7;
          iVar19 = iVar19 + 1;
        } while (cVar7 != '\0');
        pcVar8 = strchr("!:?+=>",uStack_d40 & 0xff);
        if (pcVar8 != (char *)0x0) {
          iVar19 = 0;
          do {
            cVar7 = *(char *)((int)&uStack_d40 + iVar19 + 1);
            (&DAT_006f2c30)[iVar19] = cVar7;
            iVar19 = iVar19 + 1;
          } while (cVar7 != '\0');
        }
      }
      else {
        pbVar15 = (byte *)MessageResource("WEAR_ALREADY");
        if ((char)local_14ac == '\0') {
          FUN_004f6510();
        }
        pbVar18 = pbVar15;
        do {
          bVar4 = *pbVar18;
          pbVar18 = pbVar18 + 1;
          pbVar18[0x6f2c2f - (int)pbVar15] = bVar4;
        } while (bVar4 != 0);
        pcVar8 = strchr("!:?+=>",(uint)*pbVar15);
        if (pcVar8 != (char *)0x0) {
          pbVar18 = pbVar15 + 1;
          do {
            bVar4 = *pbVar18;
            pbVar18 = pbVar18 + 1;
            pbVar18[0x6f2c2f - (int)(pbVar15 + 1)] = bVar4;
          } while (bVar4 != 0);
        }
      }
    }
    else {
      FUN_0044bdb0();
    }
  }
  else if (maximum == 0x1a8) {
    if ((&DAT_006eedbf)[iVar22] == '\0') {
      if ((char)local_14ac == '\0') {
        FUN_004f6510();
      }
      iVar19 = 0;
      do {
        cVar7 = *(char *)((int)&uStack_d40 + iVar19);
        (&DAT_006f2c30)[iVar19] = cVar7;
        iVar19 = iVar19 + 1;
      } while (cVar7 != '\0');
      pcVar8 = strchr("!:?+=>",uStack_d40 & 0xff);
      if (pcVar8 != (char *)0x0) {
        iVar19 = 0;
        do {
          cVar7 = *(char *)((int)&uStack_d40 + iVar19 + 1);
          (&DAT_006f2c30)[iVar19] = cVar7;
          iVar19 = iVar19 + 1;
        } while (cVar7 != '\0');
      }
    }
    else {
      pbVar15 = (byte *)MessageResource("CANT_DROP_WORN");
      if ((char)local_14ac == '\0') {
        FUN_004f6510();
      }
      pbVar18 = pbVar15;
      do {
        bVar4 = *pbVar18;
        pbVar18 = pbVar18 + 1;
        pbVar18[0x6f2c2f - (int)pbVar15] = bVar4;
      } while (bVar4 != 0);
      pcVar8 = strchr("!:?+=>",(uint)*pbVar15);
      if (pcVar8 != (char *)0x0) {
        pbVar18 = pbVar15 + 1;
        do {
          bVar4 = *pbVar18;
          pbVar18 = pbVar18 + 1;
          pbVar18[0x6f2c2f - (int)(pbVar15 + 1)] = bVar4;
        } while (bVar4 != 0);
      }
    }
  }
  else if (maximum == 0x1aa) {
    if ((&DAT_006eedc3)[iVar22] == '\0') {
      if ((char)local_14ac == '\0') {
        FUN_004f6510();
      }
      iVar19 = 0;
      do {
        cVar7 = *(char *)((int)&uStack_d40 + iVar19);
        (&DAT_006f2c30)[iVar19] = cVar7;
        iVar19 = iVar19 + 1;
      } while (cVar7 != '\0');
      pcVar8 = strchr("!:?+=>",uStack_d40 & 0xff);
      if (pcVar8 != (char *)0x0) {
        iVar19 = 0;
        do {
          cVar7 = *(char *)((int)&uStack_d40 + iVar19 + 1);
          (&DAT_006f2c30)[iVar19] = cVar7;
          iVar19 = iVar19 + 1;
        } while (cVar7 != '\0');
      }
    }
    else {
      pbVar15 = (byte *)MessageResource("TAKEOFF_CANT");
      if ((char)local_14ac == '\0') {
        FUN_004f6510();
      }
      pbVar18 = pbVar15;
      do {
        bVar4 = *pbVar18;
        pbVar18 = pbVar18 + 1;
        pbVar18[0x6f2c2f - (int)pbVar15] = bVar4;
      } while (bVar4 != 0);
      pcVar8 = strchr("!:?+=>",(uint)*pbVar15);
      if (pcVar8 != (char *)0x0) {
        pbVar18 = pbVar15 + 1;
        do {
          bVar4 = *pbVar18;
          pbVar18 = pbVar18 + 1;
          pbVar18[0x6f2c2f - (int)(pbVar15 + 1)] = bVar4;
        } while (bVar4 != 0);
      }
    }
  }
  else {
    if ((char)local_14ac == '\0') {
      FUN_004f6510();
    }
    iVar19 = 0;
    do {
      cVar7 = *(char *)((int)&uStack_d40 + iVar19);
      (&DAT_006f2c30)[iVar19] = cVar7;
      iVar19 = iVar19 + 1;
    } while (cVar7 != '\0');
    pcVar8 = strchr("!:?+=>",uStack_d40 & 0xff);
    if (pcVar8 != (char *)0x0) {
      iVar19 = 0;
      do {
        cVar7 = *(char *)((int)&uStack_d40 + iVar19 + 1);
        (&DAT_006f2c30)[iVar19] = cVar7;
        iVar19 = iVar19 + 1;
      } while (cVar7 != '\0');
    }
  }
  memset(&DAT_005e6ac0,0,0x400);
  uStack_d88 = _DAT_005ddac0;
  uStack_d84 = _UNK_005ddac4;
  uStack_d80 = _UNK_005ddac8;
  uStack_d7c = _UNK_005ddacc;
  SDL_UpperBlit();
  DAT_065bba5c = 0;
  local_14c8 = 1;
  iVar19 = local_14c8;
  uVar9 = local_14c4;
  if ((char)local_14ac != '\0') goto LAB_0045523b;
  goto LAB_004555f0;
LAB_004572e7:
  (&DAT_006f30b8)[iVar19 * 8] = uVar13;
LAB_004572f0:
  DAT_006f7468 = DAT_006ea934;
  DAT_006f78d8 = DAT_006f78dc;
  DAT_006f309c = mask;
  pcVar8 = title;
  do {
    cVar7 = *pcVar8;
    pcVar8[(int)s_undefined_005e23f0 - (int)title] = cVar7;
    pcVar8 = pcVar8 + 1;
  } while (cVar7 != '\0');
LAB_004573f0:
  iVar19 = 1;
  local_14c8 = 1;
  uVar9 = local_14c4;
  if ((((&DAT_006eedb8)[iVar16 * 8] != 0) && ((local_14c4 == 0 || (local_148c == 1)))) &&
     (local_14c9 == '\0')) {
    DAT_0659f958 = 0;
    if (DAT_006ea884 == 0) {
      FUN_0050dad0();
    }
    else {
      SDL_UpperBlit();
      if (DAT_065bba5c == 0) {
        FUN_0050af90();
        if ((DAT_065bbcd8 != 0) && (FUN_00510040(), DAT_065bbcd8 == 2)) {
          DAT_065bbcd8 = 0;
        }
        FUN_0050b3c0();
        if (DAT_0a5c1c54 == 0) {
          SDL_RenderPresent();
        }
      }
    }
    DAT_006f7468 = DAT_006ea934;
    DAT_006f78d8 = DAT_006f78dc;
    DAT_006f309c = mask;
    pcVar8 = title;
    do {
      cVar7 = *pcVar8;
      pcVar8[(int)s_undefined_005e23f0 - (int)title] = cVar7;
      pcVar8 = pcVar8 + 1;
    } while (cVar7 != '\0');
    DAT_0659f958 = 0;
    iVar19 = __security_check_cookie(local_c ^ (uint)auStack_14cc);
    return iVar19;
  }
  goto LAB_004555f0;
LAB_00457573:
  do {
    iVar19 = SDL_PollEvent();
  } while (iVar19 != 0);
  SDL_StartTextInput();
  if (local_14af != '\0') {
    iVar19 = 0;
    do {
      if (49999 < (int)(&DAT_0a72acd0)[iVar19]) {
        puVar14 = (undefined4 *)FUN_004c0190();
        puVar24 = local_13d8;
        for (iVar16 = 0x2b; iVar16 != 0; iVar16 = iVar16 + -1) {
          *puVar24 = *puVar14;
          puVar14 = puVar14 + 1;
          puVar24 = puVar24 + 1;
        }
        if ((bStack_1372 & 0x80) != 0) {
          if (iVar19 != 1000) {
            FUN_00451250();
          }
          break;
        }
      }
      iVar19 = iVar19 + 1;
    } while (iVar19 < 100);
    iVar19 = 0;
    do {
      if (49999 < (int)(&DAT_0a72acd0)[iVar19]) {
        puVar14 = (undefined4 *)FUN_004c0190();
        puVar24 = local_13d8;
        for (iVar16 = 0x2b; iVar16 != 0; iVar16 = iVar16 + -1) {
          *puVar24 = *puVar14;
          puVar14 = puVar14 + 1;
          puVar24 = puVar24 + 1;
        }
        if ((bStack_1372 & 0x10) != 0) {
          if (iVar19 != 1000) {
            FUN_00451250();
          }
          break;
        }
      }
      iVar19 = iVar19 + 1;
    } while (iVar19 < 100);
    DAT_0458cce3 = 1;
  }
  if (local_14ae != '\0') {
    iVar19 = 0;
    do {
      if (49999 < (int)(&DAT_0a72acd0)[iVar19]) {
        puVar14 = (undefined4 *)FUN_004c0190();
        puVar24 = local_13d8;
        for (iVar16 = 0x2b; iVar16 != 0; iVar16 = iVar16 + -1) {
          *puVar24 = *puVar14;
          puVar14 = puVar14 + 1;
          puVar24 = puVar24 + 1;
        }
        if ((bStack_1372 & 0x80) != 0) {
          if (iVar19 != 1000) {
            FUN_00451250();
          }
          break;
        }
      }
      iVar19 = iVar19 + 1;
    } while (iVar19 < 100);
    DAT_0458cce3 = 1;
  }
  if (local_14ad != '\0') {
    iVar19 = 0;
    do {
      if (49999 < (int)(&DAT_0a72acd0)[iVar19]) {
        puVar14 = (undefined4 *)FUN_004c0190();
        puVar24 = local_13d8;
        for (iVar16 = 0x2b; iVar16 != 0; iVar16 = iVar16 + -1) {
          *puVar24 = *puVar14;
          puVar14 = puVar14 + 1;
          puVar24 = puVar24 + 1;
        }
        if ((bStack_1372 & 0x10) != 0) {
          if (iVar19 != 1000) {
            FUN_00451250();
          }
          DAT_0458cce3 = 1;
          goto LAB_0045523b;
        }
      }
      iVar19 = iVar19 + 1;
    } while (iVar19 < 100);
    DAT_0458cce3 = 1;
  }
LAB_0045523b:
  iVar19 = __security_check_cookie(local_c ^ (uint)auStack_14cc);
  return iVar19;
}


/* Extracted native producer 004581f0; inventory-errors */

int __fastcall SelectInventory(char *title,char *verb,uint flags,uint mask,int maximum)

{
  int iVar1;
  
  DAT_006f30a0 = 0;
  iVar1 = Inventory(2,-1,DAT_0a6d1c9c,DAT_0a72bd40,title,verb,flags,mask,maximum);
  if (-1 < iVar1) {
    DAT_006f30a0 = (&DAT_006eedb8)[iVar1 * 8];
    iVar1 = (&DAT_006eedac)[iVar1 * 8];
  }
  return iVar1;
}

