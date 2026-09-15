// ========================================================
// Function: FUN_010026a5 at 010026a5
// ========================================================

undefined4 * __thiscall FUN_010026a5(void *this,byte param_1)

{
  FUN_0100888a(this);
  if ((param_1 & 1) != 0) {
    FUN_01009193(this);
  }
  return this;
}



// ========================================================
// Function: `scalar_deleting_destructor' at 010026cb
// ========================================================

/* Library Function - Single Match
    public: void * __thiscall CProperty::`scalar deleting destructor'(unsigned int)
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

void * __thiscall CProperty::_scalar_deleting_destructor_(CProperty *this,uint param_1)

{
  FreeValue(this);
  if ((param_1 & 1) != 0) {
    FUN_01009193(this);
  }
  return this;
}



// ========================================================
// Function: FUN_010026f1 at 010026f1
// ========================================================

LPVOID __thiscall FUN_010026f1(void *this,byte param_1)

{
  FUN_010080d7((int)this);
  if ((param_1 & 1) != 0) {
    FUN_01009193(this);
  }
  return this;
}



// ========================================================
// Function: FUN_01002717 at 01002717
// ========================================================

void FUN_01002717(HDC param_1,int param_2,int param_3,int *param_4,int *param_5)

{
  int *piVar1;
  HDC hdc;
  HBITMAP h;
  HGDIOBJ h_00;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_14;
  int local_c;
  int local_8;
  
  piVar1 = param_5;
  hdc = CreateCompatibleDC(param_1);
  h = LoadBitmapW(DAT_01012000,L"FELT");
  h_00 = SelectObject(hdc,h);
  iVar3 = param_5[2] - *param_5;
  iVar8 = 0x3f - (*param_5 - *param_4) % 0x3f;
  iVar4 = (iVar3 - iVar8) % 0x3f;
  iVar6 = 0x40 - (param_5[1] - param_4[1]) % 0x40;
  iVar5 = ((param_5[3] - param_5[1]) - iVar6) % 0x40;
  iVar2 = param_5[3] - param_5[1];
  param_5 = (int *)param_3;
  if (param_3 < iVar2) {
    do {
      if (param_4[3] <= (int)param_5) break;
      iVar7 = param_2;
      if ((int)param_5 < iVar6 + param_3) {
        local_14 = 0x40 - iVar6;
        local_c = iVar6;
      }
      else {
        local_14 = 0;
        local_c = iVar5;
        if (param_5 != (int *)((iVar2 - iVar5) - param_3)) {
          local_c = 0x40;
        }
      }
      for (; (iVar7 < iVar3 && (iVar7 < param_4[2])); iVar7 = iVar7 + local_8) {
        if (iVar7 < iVar8 + param_2) {
          iVar2 = 0x3f - iVar8;
          local_8 = iVar8;
        }
        else {
          local_8 = iVar4;
          if (iVar7 != (iVar3 - iVar4) - param_2) {
            local_8 = 0x3f;
          }
          iVar2 = 0;
        }
        BitBlt(param_1,iVar7,(int)param_5,local_8,local_c,hdc,iVar2,local_14,0xcc0020);
        iVar3 = piVar1[2] - *piVar1;
      }
      param_5 = (int *)((int)param_5 + local_c);
      iVar2 = piVar1[3] - piVar1[1];
    } while ((int)param_5 < iVar2);
  }
  SelectObject(hdc,h_00);
  DeleteObject(h);
  DeleteDC(hdc);
  return;
}



// ========================================================
// Function: FUN_01002899 at 01002899
// ========================================================

void FUN_01002899(HDC param_1,int param_2,int param_3,uint param_4,int param_5,int param_6)

{
  int y;
  HBITMAP h;
  HDC hdc;
  HGDIOBJ h_00;
  wchar_t *lpBitmapName;
  WCHAR local_30 [20];
  uint local_8;
  
  local_8 = DAT_0101107c;
  if (((int)param_4 < 1) || (0x34 < (int)param_4)) {
    if (param_4 == 0x69) {
      lpBitmapName = L"FELT";
    }
    else if (param_4 == 0x68) {
      lpBitmapName = L"CARDBACK";
    }
    else {
      lpBitmapName = (wchar_t *)(param_4 & 0xffff);
    }
  }
  else {
    wsprintfW(local_30,L"CARD%d",param_4);
    lpBitmapName = local_30;
  }
  h = LoadBitmapW(DAT_01012000,lpBitmapName);
  hdc = CreateCompatibleDC(param_1);
  h_00 = SelectObject(hdc,h);
  BitBlt(param_1,param_2,param_3,0x47,0x60,hdc,0,0,0xcc0020);
  SelectObject(hdc,h_00);
  DeleteObject(h);
  DeleteDC(hdc);
  if (param_5 != 0) {
    SetPixel(param_1,param_2,param_3,0x8000);
    SetPixel(param_1,param_2 + 1,param_3,0x8000);
    SetPixel(param_1,param_2,param_3 + 1,0x8000);
    SetPixel(param_1,param_2 + 0x46,param_3,0x8000);
    SetPixel(param_1,param_2 + 0x45,param_3,0x8000);
    SetPixel(param_1,param_2 + 0x46,param_3 + 1,0x8000);
  }
  if (param_6 != 0) {
    SetPixel(param_1,param_2,param_3 + 0x5f,0x8000);
    SetPixel(param_1,param_2 + 1,param_3 + 0x5f,0x8000);
    SetPixel(param_1,param_2,param_3 + 0x5e,0x8000);
    SetPixel(param_1,param_2 + 0x46,param_3 + 0x5f,0x8000);
    SetPixel(param_1,param_2 + 0x45,param_3 + 0x5f,0x8000);
    SetPixel(param_1,param_2 + 0x46,param_3 + 0x5e,0x8000);
  }
  if (((0xd < (int)param_4) && ((int)param_4 < 0x18)) ||
     ((0x1a < (int)param_4 && ((int)param_4 < 0x25)))) {
    y = param_3 + 2;
    MoveToEx(param_1,param_2,y,(LPPOINT)0x0);
    LineTo(param_1,param_2,param_3 + 0x5d);
    LineTo(param_1,param_2 + 2,param_3 + 0x5f);
    LineTo(param_1,param_2 + 0x44,param_3 + 0x5f);
    LineTo(param_1,param_2 + 0x46,param_3 + 0x5d);
    LineTo(param_1,param_2 + 0x46,y);
    LineTo(param_1,param_2 + 0x44,param_3);
    LineTo(param_1,param_2 + 2,param_3);
    LineTo(param_1,param_2,y);
  }
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_01002ab2 at 01002ab2
// ========================================================

int __thiscall FUN_01002ab2(void *this,int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == -1) {
    iVar1 = 10;
  }
  else {
    iVar1 = *(int *)(*(int *)((int)this + 8) + 0x50 + param_1 * 4);
    if (param_2 < iVar1) {
      iVar1 = param_2 * 7 + 10;
    }
    else {
      iVar1 = (param_2 - iVar1) * *(int *)((int)this + param_1 * 4 + 0x30) + 10 + iVar1 * 7;
    }
  }
  return iVar1;
}



// ========================================================
// Function: FUN_01002af5 at 01002af5
// ========================================================

int __thiscall FUN_01002af5(void *this,int param_1)

{
  return (*(int *)((int)this + 0x14) + 0x47) * 9 + param_1 * -0xc + *(int *)((int)this + 0x18);
}



// ========================================================
// Function: FUN_01002b1a at 01002b1a
// ========================================================

int __fastcall FUN_01002b1a(undefined4 *param_1)

{
  tagRECT local_14;
  
  GetClientRect((HWND)*param_1,&local_14);
  return local_14.bottom + -0x6a;
}



// ========================================================
// Function: FUN_01002b3b at 01002b3b
// ========================================================

void __thiscall FUN_01002b3b(void *this,int *param_1)

{
  int iVar1;
  void *this_00;
  tagRECT local_14;
  
  GetClientRect(*(HWND *)this,&local_14);
  iVar1 = FUN_01002af5(this,((*(int *)(*(int *)((int)this + 4) + 8) -
                             *(int *)(*(int *)((int)this + 4) + 0x10)) + 9) / 10 + -1);
  *param_1 = iVar1;
  iVar1 = FUN_01002af5(this_00,0);
  param_1[2] = iVar1 + 0x47;
  param_1[1] = local_14.bottom + -0x6a;
  param_1[3] = local_14.bottom + -10;
  return;
}



// ========================================================
// Function: FUN_01002b9a at 01002b9a
// ========================================================

int __thiscall FUN_01002b9a(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (((*(int *)((int)this + 0x18) <= param_1) &&
      (iVar1 = param_1 - *(int *)((int)this + 0x18), iVar3 = *(int *)((int)this + 0x14) + 0x47,
      iVar2 = iVar1 / iVar3, iVar1 % iVar3 < 0x48)) && (iVar2 < 10)) {
    return iVar2;
  }
  return -2;
}



// ========================================================
// Function: FUN_01002bcc at 01002bcc
// ========================================================

int __thiscall FUN_01002bcc(void *this,int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  undefined3 extraout_var;
  int iVar6;
  int iVar7;
  
  if (param_2 < 10) {
    iVar6 = -2;
  }
  else {
    iVar1 = param_2 + -10;
    bVar5 = FUN_01007db9(*(void **)((int)this + 8),param_1);
    if ((CONCAT31(extraout_var,bVar5) == 0) || (0x5f < iVar1)) {
      iVar2 = *(int *)(*(int *)((int)this + 8) + 0x28 + param_1 * 4);
      iVar3 = *(int *)(*(int *)((int)this + 8) + 0x50 + param_1 * 4);
      iVar4 = *(int *)((int)this + param_1 * 4 + 0x30);
      iVar6 = -2;
      if (iVar1 < iVar3 * 7) {
        iVar6 = iVar1 / 7;
      }
      else {
        iVar7 = ((iVar2 - iVar3) + -1) * iVar4 + iVar3 * 7;
        if (iVar1 < iVar7) {
          iVar6 = (iVar1 + iVar3 * -7) / iVar4 + iVar3;
        }
        else if (iVar1 < iVar7 + 0x60) {
          iVar6 = iVar2 + -1;
        }
      }
    }
    else {
      iVar6 = -1;
    }
  }
  return iVar6;
}



// ========================================================
// Function: FUN_01002c59 at 01002c59
// ========================================================

void __thiscall FUN_01002c59(void *this,int param_1,int param_2,int param_3,int *param_4)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  
  iVar2 = (*(int *)((int)this + 0x14) + 0x47) * param_1 + *(int *)((int)this + 0x18);
  *param_4 = iVar2;
  param_4[2] = iVar2 + 0x47;
  iVar2 = FUN_01002ab2(this,param_1,param_2);
  param_4[1] = iVar2;
  iVar2 = *(int *)((int)*(void **)((int)this + 8) + param_1 * 4 + 0x50);
  bVar1 = FUN_01007db9(*(void **)((int)this + 8),param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    if (param_2 < iVar2) {
      if (iVar2 <= param_3) {
        iVar2 = (param_3 - iVar2) * *(int *)((int)this + param_1 * 4 + 0x30) + 0x6a + iVar2 * 7;
        goto LAB_01002ce1;
      }
      iVar2 = (param_3 - param_2) * 7;
    }
    else {
      iVar2 = (param_3 - param_2) * *(int *)((int)this + param_1 * 4 + 0x30);
    }
    iVar2 = iVar2 + 0x60 + param_4[1];
  }
  else {
    iVar2 = param_4[1] + 0x60;
  }
LAB_01002ce1:
  param_4[3] = iVar2;
  return;
}



// ========================================================
// Function: FUN_01002cf0 at 01002cf0
// ========================================================

void __thiscall FUN_01002cf0(void *this,int param_1,int param_2,int *param_3)

{
  FUN_01002c59(this,param_1,param_2,*(int *)(*(int *)((int)this + 8) + 0x28 + param_1 * 4) + -1,
               param_3);
  return;
}



// ========================================================
// Function: FUN_01002d16 at 01002d16
// ========================================================

int __thiscall FUN_01002d16(void *this,int param_1,int param_2)

{
  void *this_00;
  int iVar1;
  int iVar2;
  
  if (param_2 == -1) {
    iVar1 = 0x6c;
  }
  else {
    iVar1 = FUN_01007ecf(*(void **)((int)this + 8),param_1,param_2);
    iVar2 = FUN_0100741e(*(void **)((int)this + 4),iVar1);
    if (iVar2 == 0) {
      iVar1 = 0x68;
    }
    else {
      this_00 = *(void **)((int)this + 4);
      iVar2 = FUN_01007439(this_00,iVar1);
      iVar1 = FUN_01007453(this_00,iVar1);
      iVar1 = iVar2 * 0xd + 1 + iVar1;
    }
  }
  return iVar1;
}



// ========================================================
// Function: FUN_01002d75 at 01002d75
// ========================================================

void __fastcall FUN_01002d75(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(param_1 + 0xf88);
  iVar2 = 3;
  do {
    puVar1[-2] = 0;
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1 = puVar1 + 7;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (*(int *)(param_1 + 0xf5c) == 0) {
    if (**(int **)(param_1 + 4) == 1) {
      *(undefined4 *)(param_1 + 0xf80) = *(undefined4 *)(param_1 + 0xf58);
      return;
    }
    if (**(int **)(param_1 + 4) == 2) {
      *(undefined4 *)(param_1 + 0xf9c) = *(undefined4 *)(param_1 + 0xf58);
      return;
    }
    *(undefined4 *)(param_1 + 0xfb8) = *(undefined4 *)(param_1 + 0xf58);
  }
  return;
}



// ========================================================
// Function: FUN_01002ddb at 01002ddb
// ========================================================

undefined4 __thiscall FUN_01002ddb(void *this,int param_1,int param_2)

{
  void *this_00;
  bool bVar1;
  undefined3 extraout_var;
  undefined4 uVar2;
  int iVar3;
  
  bVar1 = FUN_01007db9(*(void **)((int)this + 8),param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    this_00 = *(void **)((int)this + 4);
    iVar3 = FUN_01007ecf(*(void **)((int)this + 8),param_1,param_2);
    uVar2 = FUN_0100741e(this_00,iVar3);
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ========================================================
// Function: FUN_01002e1a at 01002e1a
// ========================================================

undefined4 __thiscall FUN_01002e1a(void *this,int param_1,int param_2)

{
  void *this_00;
  bool bVar1;
  undefined3 extraout_var;
  undefined4 uVar2;
  int iVar3;
  
  bVar1 = FUN_01007db9(*(void **)((int)this + 8),param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    this_00 = *(void **)((int)this + 4);
    iVar3 = FUN_01007ecf(*(void **)((int)this + 8),param_1,param_2);
    uVar2 = FUN_01007439(this_00,iVar3);
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



// ========================================================
// Function: FUN_01002e59 at 01002e59
// ========================================================

undefined4 __thiscall FUN_01002e59(void *this,int param_1,int param_2)

{
  void *this_00;
  bool bVar1;
  undefined3 extraout_var;
  undefined4 uVar2;
  int iVar3;
  
  bVar1 = FUN_01007db9(*(void **)((int)this + 8),param_1);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    this_00 = *(void **)((int)this + 4);
    iVar3 = FUN_01007ecf(*(void **)((int)this + 8),param_1,param_2);
    uVar2 = FUN_01007453(this_00,iVar3);
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



// ========================================================
// Function: FUN_01002e98 at 01002e98
// ========================================================

undefined4 __fastcall FUN_01002e98(undefined4 *param_1)

{
  int iVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  int *piVar4;
  tagRECT local_34;
  RECT local_24;
  int local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_10 = 0;
  GetClientRect((HWND)*param_1,&local_34);
  if (local_34.bottom < 0x6b) {
    local_10 = 0;
  }
  else {
    local_8 = 0;
    local_c = -8 - (int)param_1;
    piVar4 = param_1 + 0xc;
    do {
      bVar2 = FUN_01007db9((void *)param_1[2],local_8);
      if (CONCAT31(extraout_var,bVar2) == 0) {
        local_14 = *piVar4;
        *piVar4 = 0x1c;
        iVar1 = *(int *)((int)piVar4 + param_1[2] + local_c);
        while( true ) {
          FUN_01002cf0(param_1,local_8,iVar1 + -1,&local_24.left);
          iVar3 = FUN_01002b1a(param_1);
          if ((local_24.bottom < iVar3) ||
             (((*piVar4 < 0x10 && (iVar3 = FUN_01002b1a(param_1), local_24.top < iVar3 + -0x10)) ||
              (*piVar4 < 1)))) break;
          *piVar4 = *piVar4 + -1;
        }
        if (*piVar4 != local_14) {
          local_24.top = 0;
          local_24.bottom = local_34.bottom;
          InvalidateRect((HWND)*param_1,&local_24,1);
          local_10 = 1;
        }
      }
      local_8 = local_8 + 1;
      piVar4 = piVar4 + 1;
    } while (local_8 < 10);
  }
  return local_10;
}



// ========================================================
// Function: FUN_01002f77 at 01002f77
// ========================================================

undefined4 FUN_01002f77(HWND param_1,int param_2,short param_3)

{
  BOOL BVar1;
  HWND hWnd;
  tagRECT *lpRect;
  INT_PTR nResult;
  tagMSG local_40;
  tagRECT local_24;
  tagRECT local_14;
  
  if (param_2 == 0x110) {
    lpRect = &local_24;
    hWnd = GetParent(param_1);
    GetWindowRect(hWnd,lpRect);
    GetWindowRect(param_1,&local_14);
    MoveWindow(param_1,(local_24.right - (local_14.right - local_14.left)) + -0x14,
               (local_24.bottom - (local_14.bottom - local_14.top)) + -10,
               local_14.right - local_14.left,local_14.bottom - local_14.top,1);
    SetTimer(param_1,1,0x14,(TIMERPROC)0x0);
  }
  else {
    if (param_2 != 0x111) {
      if (param_2 == 0x113) {
        FUN_01008d21(DAT_01012014);
        do {
          BVar1 = PeekMessageW(&local_40,param_1,0x113,0x113,1);
        } while (BVar1 != 0);
      }
      return 0;
    }
    if (param_3 == 1) {
      nResult = 1;
    }
    else {
      if (param_3 != 2) {
        return 0;
      }
      nResult = 2;
    }
    EndDialog(param_1,nResult);
  }
  return 1;
}



// ========================================================
// Function: FUN_01003038 at 01003038
// ========================================================

undefined4 __thiscall FUN_01003038(void *this,int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_8;
  
  iVar5 = *(int *)(*(int *)((int)this + 8) + 0x28 + param_1 * 4);
  if (iVar5 < 0xd) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_01002e1a(this,param_1,iVar5 + -1);
    iVar3 = FUN_01002e59(this,param_1,iVar5 + -1);
    local_8 = 2;
    iVar5 = iVar5 + -2;
    do {
      iVar3 = iVar3 + 1;
      iVar4 = FUN_01002ddb(this,param_1,iVar5);
      if (((iVar4 == 0) || (iVar4 = FUN_01002e59(this,param_1,iVar5), iVar4 != iVar3)) ||
         (iVar4 = FUN_01002e1a(this,param_1,iVar5), iVar4 != iVar2)) {
        return 0;
      }
      local_8 = local_8 + 1;
      iVar5 = iVar5 + -1;
    } while (local_8 < 0xe);
    uVar1 = 1;
  }
  return uVar1;
}



// ========================================================
// Function: FUN_010030ca at 010030ca
// ========================================================

undefined4 __thiscall FUN_010030ca(void *this,undefined4 *param_1)

{
  undefined4 uVar1;
  
  if (*(int *)((int)this + 0x60) < 0x1f) {
    *(undefined4 *)((int)this + *(int *)((int)this + 0x60) * 0x18 + 0x68) = *param_1;
    *(undefined4 *)((int)this + *(int *)((int)this + 0x60) * 0x18 + 0x6c) = param_1[1];
    *(undefined4 *)((int)this + *(int *)((int)this + 0x60) * 0x18 + 0x70) = param_1[2];
    *(undefined4 *)((int)this + *(int *)((int)this + 0x60) * 0x18 + 0x74) = param_1[3];
    *(undefined4 *)((int)this + (*(int *)((int)this + 0x60) + 5) * 0x18) = param_1[4];
    *(undefined4 *)((int)this + *(int *)((int)this + 0x60) * 0x18 + 0x7c) = param_1[5];
    *(int *)((int)this + 0x60) = *(int *)((int)this + 0x60) + 1;
    uVar1 = *(undefined4 *)((int)this + 0x60);
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



// ========================================================
// Function: FUN_0100313c at 0100313c
// ========================================================

int __fastcall FUN_0100313c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 100);
  iVar1 = iVar2 + 1;
  *(int *)(param_1 + 100) = iVar1;
  if (iVar1 == *(int *)(param_1 + 0x60)) {
    *(undefined4 *)(param_1 + 100) = 0;
  }
  return param_1 + 0x68 + iVar2 * 0x18;
}



// ========================================================
// Function: FUN_0100315b at 0100315b
// ========================================================

undefined4 __thiscall FUN_0100315b(void *this,int param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined3 extraout_var;
  undefined4 uVar4;
  
  uVar4 = 2;
  iVar2 = FUN_01002e1a(this,param_1,param_2);
  iVar3 = FUN_01002e1a(this,param_3,param_4);
  if (iVar2 == iVar3) {
    uVar4 = 3;
  }
  else {
    bVar1 = FUN_01007db9(*(void **)((int)this + 8),param_3);
    if (CONCAT31(extraout_var,bVar1) != 0) {
      uVar4 = 1;
    }
  }
  return uVar4;
}



// ========================================================
// Function: FUN_010031ab at 010031ab
// ========================================================

void __fastcall FUN_010031ab(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 local_28 [6];
  undefined4 *local_10;
  int local_c;
  int local_8;
  
  local_8 = 1;
  if (1 < *(int *)(param_1 + 0x60)) {
    local_10 = (undefined4 *)(param_1 + 0x68);
    puVar1 = local_10;
    local_c = local_8;
    do {
      while ((0 < local_c && ((int)puVar1[5] < (int)puVar1[0xb]))) {
        local_c = local_c + -1;
        puVar3 = puVar1;
        puVar4 = local_28;
        for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar4 = puVar4 + 1;
        }
        puVar3 = puVar1 + 6;
        puVar4 = puVar3;
        puVar5 = puVar1;
        for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar1 = puVar1 + -6;
        puVar4 = local_28;
        for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar3 = puVar3 + 1;
        }
      }
      local_8 = local_8 + 1;
      local_10 = local_10 + 6;
      puVar1 = local_10;
      local_c = local_8;
    } while (local_8 < *(int *)(param_1 + 0x60));
  }
  return;
}



// ========================================================
// Function: FUN_01003223 at 01003223
// ========================================================

void __fastcall FUN_01003223(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = *(int *)(param_1 + 0xf0c) + -1;
  if (0 < iVar1) {
    puVar3 = (undefined4 *)(param_1 + 0x368);
    puVar4 = (undefined4 *)(param_1 + 0x354);
    for (uVar2 = iVar1 * 5 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  *(int *)(param_1 + 0xf0c) = iVar1;
  return;
}



// ========================================================
// Function: FUN_01003259 at 01003259
// ========================================================

void __fastcall FUN_01003259(undefined4 *param_1)

{
  HMENU hMenu;
  
  param_1[0x3c3] = 0;
  hMenu = GetMenu((HWND)*param_1);
  EnableMenuItem(hMenu,0x9c4a,1);
  return;
}



// ========================================================
// Function: FUN_0100327c at 0100327c
// ========================================================

void __fastcall FUN_0100327c(undefined4 *param_1)

{
  DialogBoxParamW(DAT_01012000,(LPCWSTR)0x6b,(HWND)*param_1,FUN_01007565,(LPARAM)param_1);
  return;
}



// ========================================================
// Function: FUN_0100329a at 0100329a
// ========================================================

void __fastcall FUN_0100329a(undefined4 *param_1)

{
  DialogBoxParamW(DAT_01012000,(LPCWSTR)0x76,(HWND)*param_1,FUN_01007be2,(LPARAM)param_1);
  return;
}



// ========================================================
// Function: FUN_010032b8 at 010032b8
// ========================================================

void __fastcall FUN_010032b8(undefined4 *param_1)

{
  DialogBoxParamW(DAT_01012000,(LPCWSTR)0x75,(HWND)*param_1,FUN_010078d9,(LPARAM)param_1);
  return;
}



// ========================================================
// Function: FUN_010032d6 at 010032d6
// ========================================================

void __thiscall
FUN_010032d6(void *this,HDC param_1,HDC param_2,HDC param_3,HDC param_4,int *param_5,int *param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int cx;
  int y;
  int iVar4;
  int iVar5;
  int iVar6;
  int cy;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  
  iVar1 = param_5[2] - *param_5;
  iVar2 = param_5[3] - param_5[1];
  uVar9 = *param_6 - *param_5;
  uVar8 = param_6[1] - param_5[1];
  iVar3 = (uVar8 ^ (int)uVar8 >> 0x1f) - ((int)uVar8 >> 0x1f);
  cy = iVar2 - iVar3;
  cx = (uVar9 ^ (int)uVar9 >> 0x1f) - ((int)uVar9 >> 0x1f);
  y = (uint)(0 < (int)uVar8) * iVar3;
  iVar7 = (uint)((int)uVar8 < 0) * iVar3;
  if ((0 < iVar1) && (0 < iVar3)) {
    if ((int)uVar8 < 1) {
      iVar4 = cy;
      if (-1 < (int)uVar8) goto LAB_010033ab;
    }
    else {
      iVar4 = 0;
    }
    BitBlt(param_2,0,iVar4,iVar1,iVar3,param_3,0,iVar4,0xcc0020);
  }
LAB_010033ab:
  iVar4 = 0;
  if ((0 < cx) && (0 < cy)) {
    if ((int)uVar9 < 1) {
      if (-1 < (int)uVar9) goto LAB_010033dc;
      iVar4 = iVar1 - cx;
    }
    BitBlt(param_2,iVar4,y,cx,cy,param_3,iVar4,y,0xcc0020);
  }
LAB_010033dc:
  iVar4 = iVar1 - cx;
  if ((0 < iVar4 + 1) && (0 < cy + 1)) {
    BitBlt(param_3,(uint)((int)uVar9 < 0) * cx,iVar7,iVar4 + 1,cy + 1,param_3,
           (uint)(0 < (int)uVar9) * cx,y,0xcc0020);
  }
  if ((0 < iVar1) && (0 < iVar3)) {
    iVar6 = iVar3;
    if ((int)uVar8 < 1) {
      if (-1 < (int)uVar8) goto LAB_01003467;
      iVar11 = param_6[1];
      if (iVar11 < 0) {
        iVar11 = 0;
        iVar5 = *param_6;
        iVar6 = param_6[1] + iVar3;
        iVar10 = -param_6[1];
      }
      else {
        iVar5 = *param_6;
        iVar10 = 0;
      }
    }
    else {
      iVar11 = param_5[3];
      iVar5 = *param_6;
      iVar10 = cy;
    }
    BitBlt(param_3,0,iVar10,iVar1,iVar6,param_1,iVar5,iVar11,0xcc0020);
  }
LAB_01003467:
  if ((0 < cx) && (0 < cy)) {
    iVar6 = cx;
    if ((int)uVar9 < 1) {
      if (-1 < (int)uVar9) goto LAB_010034d1;
      iVar11 = *param_6;
      iVar5 = param_6[1] + iVar7;
      if (iVar11 < 0) {
        iVar10 = 0;
        iVar6 = cx + iVar11;
        iVar4 = -iVar11;
      }
      else {
        iVar4 = 0;
        iVar10 = iVar11;
      }
    }
    else {
      iVar5 = param_6[1] + iVar7;
      iVar10 = param_5[2];
    }
    BitBlt(param_3,iVar4,iVar7,iVar6,cy,param_1,iVar10,iVar5,0xcc0020);
  }
LAB_010034d1:
  BitBlt(param_1,*param_6,param_6[1],iVar1,iVar2,param_4,0,0,0xcc0020);
  if ((0 < iVar1) && (0 < iVar3)) {
    if ((int)uVar8 < 1) {
      if (-1 < (int)uVar8) goto LAB_0100352a;
      iVar2 = param_6[3];
      iVar7 = cy;
    }
    else {
      iVar2 = param_5[1];
      iVar7 = 0;
    }
    BitBlt(param_1,*param_5,iVar2,iVar1,iVar3,param_2,0,iVar7,0xcc0020);
  }
LAB_0100352a:
  if (cx < 1) {
    return;
  }
  if (cy < 1) {
    return;
  }
  iVar1 = cx;
  if ((int)uVar9 < 1) {
    if (-1 < (int)uVar9) {
      return;
    }
    iVar1 = *(int *)((int)this + 0x101c);
    if (cx <= iVar1) {
      iVar7 = iVar1 - cx;
      iVar3 = param_5[1];
      iVar2 = param_5[2] - cx;
      goto LAB_01003585;
    }
  }
  iVar7 = 0;
  iVar3 = param_5[1];
  iVar2 = *param_5;
  cx = iVar1;
LAB_01003585:
  BitBlt(param_1,iVar2,iVar3 + y,cx,cy,param_2,iVar7,y,0xcc0020);
  return;
}



// ========================================================
// Function: FUN_01003596 at 01003596
// ========================================================

void __thiscall FUN_01003596(void *this,int param_1)

{
  int iVar1;
  int *piVar2;
  
  if (**(int **)((int)this + 4) == 1) {
    piVar2 = (int *)((int)this + 0xf80);
  }
  else {
    piVar2 = (int *)((int)this + 0xf9c);
    if (**(int **)((int)this + 4) != 2) {
      piVar2 = (int *)((int)this + 0xfb8);
    }
  }
  iVar1 = *(int *)((int)this + 0xf58) + param_1;
  if (iVar1 < 0) {
    iVar1 = 0;
  }
  *(int *)((int)this + 0xf58) = iVar1;
  if (*piVar2 < iVar1) {
    *piVar2 = iVar1;
  }
  return;
}



// ========================================================
// Function: FUN_010035e2 at 010035e2
// ========================================================

int __fastcall FUN_010035e2(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0xf10);
  iVar3 = 4;
  do {
    iVar1 = iVar1 + *piVar2;
    piVar2 = piVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return iVar1;
}



// ========================================================
// Function: FUN_010035fb at 010035fb
// ========================================================

undefined * FUN_010035fb(UINT param_1)

{
  LoadStringW(DAT_01012000,param_1,(LPWSTR)&DAT_01011800,0x400);
  return &DAT_01011800;
}



// ========================================================
// Function: FUN_01003627 at 01003627
// ========================================================

void FUN_01003627(HWND param_1,UINT param_2,UINT param_3,UINT param_4)

{
  LPCWSTR pWVar1;
  WCHAR *lpCaption;
  WCHAR local_808 [1024];
  uint local_8;
  
  local_8 = DAT_0101107c;
  pWVar1 = (LPCWSTR)FUN_010035fb(param_3);
  lstrcpyW(local_808,pWVar1);
  lpCaption = local_808;
  pWVar1 = (LPCWSTR)FUN_010035fb(param_2);
  MessageBoxW(param_1,pWVar1,lpCaption,param_4);
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_01003680 at 01003680
// ========================================================

undefined4 __thiscall
FUN_01003680(void *this,undefined4 param_1,undefined4 param_2,byte param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  if (((param_3 & 1) != 0) && (*(int *)((int)this + 0x20) != 0)) {
    piVar1 = (int *)((int)this + 0xffc);
    local_14 = *piVar1;
    uStack_10 = *(undefined4 *)((int)this + 0x1000);
    uStack_c = *(undefined4 *)((int)this + 0x1004);
    iVar2 = (int)(short)param_4 - *(int *)((int)this + 0x1024);
    uStack_8 = *(undefined4 *)((int)this + 0x1008);
    iVar3 = (int)(short)((uint)param_4 >> 0x10) - *(int *)((int)this + 0x1028);
    *piVar1 = iVar2;
    *(int *)((int)this + 0x1008) = *(int *)((int)this + 0x1020) + iVar3;
    *(int *)((int)this + 0x1000) = iVar3;
    *(int *)((int)this + 0x1004) = *(int *)((int)this + 0x101c) + iVar2;
    FUN_010032d6(this,*(HDC *)((int)this + 0xfd4),*(HDC *)((int)this + 0xfe0),
                 *(HDC *)((int)this + 0xfd8),*(HDC *)((int)this + 0xfdc),&local_14,piVar1);
  }
  return 0;
}



// ========================================================
// Function: FUN_01003712 at 01003712
// ========================================================

undefined4 __thiscall FUN_01003712(void *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  HDC hDC;
  uint uVar6;
  uint in_stack_00000010;
  int iVar7;
  int iVar8;
  
  if ((((*(int *)((int)this + 0x20) == 0) &&
       (iVar3 = FUN_01002b9a(this,in_stack_00000010 & 0xffff), iVar3 != -2)) &&
      (iVar4 = FUN_01002bcc(this,iVar3,in_stack_00000010 >> 0x10), iVar4 != -2)) &&
     (*(int *)(*(int *)((int)this + 8) + 0x50 + iVar3 * 4) <= iVar4)) {
    *(undefined4 *)((int)this + 0x24) = 1;
    *(int *)((int)this + 0x28) = iVar3;
    *(int *)((int)this + 0x2c) = iVar4;
    SetCapture(*(HWND *)this);
    iVar1 = *(int *)((int)this + 0x14);
    iVar2 = *(int *)((int)this + 0x18);
    iVar5 = FUN_01002ab2(this,iVar3,iVar4);
    hDC = GetDC(*(HWND *)this);
    iVar8 = 1;
    iVar7 = 1;
    uVar6 = FUN_01002d16(this,iVar3,iVar4);
    FUN_01002899(hDC,(iVar1 + 0x47) * iVar3 + iVar2,iVar5,uVar6,iVar7,iVar8);
    ReleaseDC(*(HWND *)this,hDC);
  }
  return 0;
}



// ========================================================
// Function: FUN_01003811 at 01003811
// ========================================================

void __thiscall FUN_01003811(void *this,LPRECT param_1)

{
  int iVar1;
  
  GetClientRect(*(HWND *)this,param_1);
  iVar1 = param_1->right - param_1->left;
  param_1->left = (iVar1 + -200) / 2;
  param_1->right = (iVar1 + 200) / 2;
  iVar1 = FUN_01002b1a(this);
  param_1->bottom = param_1->bottom + -10;
  param_1->top = iVar1;
  return;
}



// ========================================================
// Function: FUN_0100385f at 0100385f
// ========================================================

void __thiscall FUN_0100385f(void *this,HDC param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  iVar2 = *(int *)((int)this + 4);
  iVar1 = FUN_01002b1a(this);
  iVar2 = *(int *)(iVar2 + 8) - *(int *)(iVar2 + 0x10);
  if (iVar2 != 0x68) {
    iVar2 = (iVar2 + 9) / 10;
    iVar4 = 0;
    if (0 < iVar2) {
      do {
        iVar8 = 1;
        iVar7 = 1;
        uVar6 = 0x68;
        iVar5 = iVar1 + param_3;
        iVar3 = FUN_01002af5(this,iVar4);
        FUN_01002899(param_1,iVar3 + param_2,iVar5,uVar6,iVar7,iVar8);
        iVar4 = iVar4 + 1;
      } while (iVar4 < iVar2);
    }
  }
  return;
}



// ========================================================
// Function: FUN_010038c3 at 010038c3
// ========================================================

void __thiscall FUN_010038c3(void *this,HDC param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int local_8;
  
  iVar1 = param_3;
  local_8 = FUN_010035e2((int)this);
  iVar2 = FUN_01002b1a(this);
  if (0 < local_8) {
    param_3 = 0;
    piVar3 = (int *)((int)this + 0xf20);
    do {
      FUN_01002899(param_1,*(int *)((int)this + 0x18) + param_3 + param_2,iVar2 + iVar1,
                   (*piVar3 + 1) * 0xd,1,1);
      param_3 = param_3 + 0xc;
      piVar3 = piVar3 + 1;
      local_8 = local_8 + -1;
    } while (local_8 != 0);
  }
  return;
}



// ========================================================
// Function: FUN_01003931 at 01003931
// ========================================================

void __thiscall FUN_01003931(void *this,int *param_1)

{
  int iVar1;
  int iVar2;
  
  *param_1 = *(int *)((int)this + 0x18);
  iVar1 = FUN_01002b1a(this);
  param_1[1] = iVar1;
  iVar2 = FUN_010035e2((int)this);
  param_1[3] = iVar1 + 0x60;
  param_1[2] = iVar2 * 0x53 + *param_1;
  return;
}



// ========================================================
// Function: FUN_0100396e at 0100396e
// ========================================================

undefined4 __thiscall FUN_0100396e(void *this,int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = param_1;
  iVar4 = *(int *)((int)*(void **)((int)this + 8) + param_1 * 4 + 0x28);
  bVar2 = FUN_01007db9(*(void **)((int)this + 8),param_1);
  if ((CONCAT31(extraout_var,bVar2) == 0) &&
     (iVar3 = FUN_01002ddb(this,param_1,param_2), iVar3 != 0)) {
    iVar4 = iVar4 + -1;
    if (iVar4 <= param_2) {
      return 1;
    }
    iVar3 = FUN_01002e1a(this,param_1,param_2);
    param_1 = FUN_01002e59(this,param_1,param_2);
    do {
      param_2 = param_2 + 1;
      if (iVar4 < param_2) {
        return 1;
      }
      param_1 = param_1 + -1;
      iVar5 = FUN_01002e1a(this,iVar1,param_2);
    } while ((iVar5 == iVar3) && (iVar5 = FUN_01002e59(this,iVar1,param_2), iVar5 == param_1));
  }
  return 0;
}



// ========================================================
// Function: FUN_01003a06 at 01003a06
// ========================================================

bool __thiscall FUN_01003a06(void *this,int param_1,int param_2,int param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)((int)*(void **)((int)this + 8) + param_3 * 4 + 0x28) + -1;
  if ((param_1 != param_3) &&
     (bVar1 = FUN_01007db9(*(void **)((int)this + 8),param_1), CONCAT31(extraout_var,bVar1) == 0)) {
    bVar1 = FUN_01007db9(*(void **)((int)this + 8),param_3);
    if (CONCAT31(extraout_var_00,bVar1) != 0) {
      return true;
    }
    iVar2 = FUN_01002ddb(this,param_3,iVar3);
    if ((iVar2 != 0) && (iVar2 = FUN_01002ddb(this,param_1,param_2), iVar2 != 0)) {
      iVar2 = FUN_01002e59(this,param_1,param_2);
      iVar3 = FUN_01002e59(this,param_3,iVar3);
      return (bool)('\x01' - (iVar3 != iVar2 + 1));
    }
  }
  return false;
}



// ========================================================
// Function: FUN_01003a90 at 01003a90
// ========================================================

void __fastcall FUN_01003a90(void *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined3 extraout_var;
  int iVar4;
  uint local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  *(undefined4 *)((int)param_1 + 0x60) = 0;
  *(undefined4 *)((int)param_1 + 100) = 0;
  local_8 = 0;
  local_18 = 0x28;
  do {
    local_c = 0;
    local_14 = 0x28;
    do {
      if (local_8 != local_c) {
        iVar2 = *(int *)(local_18 + *(int *)((int)param_1 + 8));
        iVar4 = iVar2 + -1;
        local_1c = iVar4;
        if (0 < iVar4) {
          local_10 = iVar2 + -2;
          do {
            local_1c = iVar4;
            iVar2 = FUN_01002e1a(param_1,local_8,iVar4);
            iVar3 = FUN_01002e1a(param_1,local_8,local_10);
            if (iVar2 != iVar3) break;
            iVar2 = FUN_01002e59(param_1,local_8,local_10);
            iVar3 = FUN_01002e59(param_1,local_8,iVar4);
            if (iVar3 != iVar2 + -1) break;
            iVar2 = FUN_01002ddb(param_1,local_8,local_10);
            if (iVar2 == 0) break;
            iVar4 = iVar4 + -1;
            local_10 = local_10 + -1;
            local_1c = iVar4;
          } while (0 < iVar4);
        }
        bVar1 = FUN_01003a06(param_1,local_8,iVar4,local_c);
        if (CONCAT31(extraout_var,bVar1) != 0) {
          iVar2 = *(int *)(local_14 + *(int *)((int)param_1 + 8)) + -1;
          local_20 = FUN_0100315b(param_1,local_8,iVar4,local_c,iVar2);
          if (0 < local_20) {
            local_10 = FUN_01002e1a(param_1,local_c,iVar2);
            iVar4 = FUN_01002e1a(param_1,local_8,iVar4);
            local_38 = (uint)(iVar4 == local_10);
            local_34 = local_8;
            local_30 = local_1c;
            local_2c = local_c;
            local_24 = local_20;
            local_28 = iVar2;
            FUN_010030ca(param_1,&local_38);
          }
        }
      }
      local_14 = local_14 + 4;
      local_c = local_c + 1;
    } while (local_14 < 0x50);
    local_18 = local_18 + 4;
    local_8 = local_8 + 1;
    if (0x4f < local_18) {
      *(undefined4 *)((int)param_1 + 0x5c) = 1;
      return;
    }
  } while( true );
}



// ========================================================
// Function: FUN_01003be7 at 01003be7
// ========================================================

int __thiscall FUN_01003be7(void *this,undefined4 *param_1)

{
  HMENU hMenu;
  int iVar1;
  
  iVar1 = *(int *)((int)this + 0xf0c);
  if (iVar1 == 0) {
    hMenu = GetMenu(*(HWND *)this);
    EnableMenuItem(hMenu,0x9c4a,0);
  }
  if (iVar1 == 0x96) {
    FUN_01003223((int)this);
    iVar1 = 0x95;
  }
  *(undefined4 *)((int)this + iVar1 * 0x14 + 0x354) = *param_1;
  *(undefined4 *)((int)this + iVar1 * 0x14 + 0x358) = param_1[1];
  *(undefined4 *)((int)this + (iVar1 * 5 + 0xd7) * 4) = param_1[2];
  *(undefined4 *)((int)this + iVar1 * 0x14 + 0x360) = param_1[3];
  *(undefined4 *)((int)this + iVar1 * 0x14 + 0x364) = param_1[4];
  *(int *)((int)this + 0xf0c) = iVar1 + 1;
  return iVar1 + 1;
}



// ========================================================
// Function: FUN_01003c6e at 01003c6e
// ========================================================

void __fastcall FUN_01003c6e(int param_1)

{
  LPCWSTR pWVar1;
  LSTATUS LVar2;
  LPDWORD pDVar3;
  DWORD ulOptions;
  LPDWORD pDVar4;
  REGSAM samDesired;
  LPBYTE pBVar5;
  int *piVar6;
  HKEY *phkResult;
  DWORD *pDVar7;
  BYTE local_90 [12];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  int local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  DWORD local_c;
  HKEY local_8;
  
  local_18 = -0x80000000;
  local_58 = -0x80000000;
  local_20 = -0x80000000;
  local_78 = -0x80000000;
  local_28 = 1;
  local_84 = 1;
  local_38 = 1;
  local_68 = 1;
  local_74 = 1;
  phkResult = &local_8;
  samDesired = 0x20019;
  ulOptions = 0;
  local_50 = 3;
  local_60 = 0;
  local_30 = 0;
  local_40 = 0;
  local_80 = 0;
  local_48 = 0;
  local_70 = 0;
  local_10 = 0;
  local_90[8] = '\0';
  local_90[9] = '\0';
  local_90[10] = '\0';
  local_90[0xb] = '\0';
  local_7c = 0;
  local_14 = 0;
  local_1c = 0;
  local_24 = 0;
  local_2c = 0;
  local_34 = 0;
  local_90[0] = '\0';
  local_90[1] = '\0';
  local_90[2] = '\0';
  local_90[3] = '\0';
  local_3c = 0;
  local_44 = 0;
  local_4c = 0;
  local_54 = 0;
  local_5c = 0;
  local_64 = 0;
  local_90[4] = '\0';
  local_90[5] = '\0';
  local_90[6] = '\0';
  local_90[7] = '\0';
  local_6c = 0;
  pWVar1 = (LPCWSTR)FUN_010035fb(9);
  LVar2 = RegOpenKeyExW((HKEY)0x80000001,pWVar1,ulOptions,samDesired,phkResult);
  if (LVar2 == 0) {
    pDVar7 = &local_c;
    pBVar5 = (LPBYTE)&local_50;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    local_c = 4;
    pWVar1 = (LPCWSTR)FUN_010035fb(10);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,pBVar5,pDVar7);
    pDVar7 = &local_c;
    piVar6 = &local_18;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0xb);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,(LPBYTE)piVar6,pDVar7);
    pDVar7 = &local_c;
    piVar6 = &local_58;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0xc);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,(LPBYTE)piVar6,pDVar7);
    pDVar7 = &local_c;
    piVar6 = &local_20;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0xd);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,(LPBYTE)piVar6,pDVar7);
    pDVar7 = &local_c;
    piVar6 = &local_78;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0xe);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,(LPBYTE)piVar6,pDVar7);
    pDVar7 = &local_c;
    pBVar5 = (LPBYTE)&local_28;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x15);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,pBVar5,pDVar7);
    pDVar7 = &local_c;
    pBVar5 = (LPBYTE)&local_60;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x16);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,pBVar5,pDVar7);
    pDVar7 = &local_c;
    pBVar5 = (LPBYTE)&local_30;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x17);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,pBVar5,pDVar7);
    pDVar7 = &local_c;
    pBVar5 = (LPBYTE)&local_84;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x18);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,pBVar5,pDVar7);
    pDVar7 = &local_c;
    pBVar5 = (LPBYTE)&local_38;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x19);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,pBVar5,pDVar7);
    pDVar7 = &local_c;
    pBVar5 = (LPBYTE)&local_68;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x33);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,pBVar5,pDVar7);
    pDVar7 = &local_c;
    pBVar5 = (LPBYTE)&local_74;
    pDVar4 = (LPDWORD)0x0;
    pDVar3 = (LPDWORD)0x0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x31);
    RegQueryValueExW(local_8,pWVar1,pDVar3,pDVar4,pBVar5,pDVar7);
    RegQueryValueExW(local_8,L"HighScore_Easy",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_40,&local_c)
    ;
    RegQueryValueExW(local_8,L"Wins_Easy",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_80,&local_c);
    RegQueryValueExW(local_8,L"Losses_Easy",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_48,&local_c);
    RegQueryValueExW(local_8,L"StreakWins_Easy",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_70,&local_c
                    );
    RegQueryValueExW(local_8,L"StreakLosses_Easy",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_10,
                     &local_c);
    RegQueryValueExW(local_8,L"StreakCurrent_Easy",(LPDWORD)0x0,(LPDWORD)0x0,local_90 + 8,&local_c);
    RegQueryValueExW(local_8,L"FWinStreak_Easy",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_7c,&local_c
                    );
    RegQueryValueExW(local_8,L"HighScore_Medium",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_14,
                     &local_c);
    RegQueryValueExW(local_8,L"Wins_Medium",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_1c,&local_c);
    RegQueryValueExW(local_8,L"Losses_Medium",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_24,&local_c);
    RegQueryValueExW(local_8,L"StreakWins_Medium",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_2c,
                     &local_c);
    RegQueryValueExW(local_8,L"StreakLosses_Medium",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_34,
                     &local_c);
    RegQueryValueExW(local_8,L"StreakCurrent_Medium",(LPDWORD)0x0,(LPDWORD)0x0,local_90,&local_c);
    RegQueryValueExW(local_8,L"FWinStreak_Medium",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_3c,
                     &local_c);
    RegQueryValueExW(local_8,L"HighScore_Difficult",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_44,
                     &local_c);
    RegQueryValueExW(local_8,L"Wins_Difficult",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_4c,&local_c)
    ;
    RegQueryValueExW(local_8,L"Losses_Difficult",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_54,
                     &local_c);
    RegQueryValueExW(local_8,L"StreakWins_Difficult",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_5c,
                     &local_c);
    RegQueryValueExW(local_8,L"StreakLosses_Difficult",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_64,
                     &local_c);
    RegQueryValueExW(local_8,L"StreakCurrent_Difficult",(LPDWORD)0x0,(LPDWORD)0x0,local_90 + 4,
                     &local_c);
    RegQueryValueExW(local_8,L"FWinStreak_Difficult",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)&local_6c,
                     &local_c);
    RegCloseKey(local_8);
  }
  *(undefined4 *)(param_1 + 0xf40) = local_50;
  *(undefined4 *)(param_1 + 0xf60) = local_28;
  *(undefined4 *)(param_1 + 0xf64) = local_60;
  *(undefined4 *)(param_1 + 0xf68) = local_30;
  *(undefined4 *)(param_1 + 0xf6c) = local_84;
  *(undefined4 *)(param_1 + 0xf70) = local_38;
  *(undefined4 *)(param_1 + 0xf74) = local_68;
  *(undefined4 *)(param_1 + 0xf80) = local_40;
  *(undefined4 *)(param_1 + 0xf84) = local_80;
  *(undefined4 *)(param_1 + 0xf88) = local_48;
  *(undefined4 *)(param_1 + 0xf8c) = local_70;
  *(undefined4 *)(param_1 + 0xf90) = local_10;
  *(undefined4 *)(param_1 + 0xf98) = local_7c;
  *(undefined4 *)(param_1 + 0xf9c) = local_14;
  *(undefined4 *)(param_1 + 4000) = local_1c;
  *(undefined4 *)(param_1 + 0xfa4) = local_24;
  *(undefined4 *)(param_1 + 0xfa8) = local_2c;
  *(undefined4 *)(param_1 + 0xfac) = local_34;
  *(undefined4 *)(param_1 + 0xfb4) = local_3c;
  *(undefined4 *)(param_1 + 0xfb8) = local_44;
  *(int *)(param_1 + 0xf44) = local_18;
  *(undefined4 *)(param_1 + 0xfbc) = local_4c;
  *(int *)(param_1 + 0xf48) = local_58;
  *(undefined4 *)(param_1 + 0xfc0) = local_54;
  *(int *)(param_1 + 0xf4c) = local_20 + local_18;
  *(undefined4 *)(param_1 + 0xfc4) = local_5c;
  *(undefined4 *)(param_1 + 0xfc8) = local_64;
  *(int *)(param_1 + 0xf50) = local_78 + local_58;
  *(undefined4 *)(param_1 + 0xfd0) = local_6c;
  **(undefined4 **)(param_1 + 4) = local_74;
  return;
}



// ========================================================
// Function: FUN_0100411f at 0100411f
// ========================================================

void __fastcall FUN_0100411f(undefined4 *param_1)

{
  LPCWSTR pWVar1;
  LSTATUS LVar2;
  BOOL BVar3;
  DWORD DVar4;
  LPWSTR lpClass;
  DWORD DVar5;
  REGSAM samDesired;
  LPSECURITY_ATTRIBUTES lpSecurityAttributes;
  int *lpData;
  tagRECT *lpData_00;
  LONG *lpData_01;
  DWORD *pDVar6;
  BYTE *pBVar7;
  HKEY *phkResult;
  DWORD DVar8;
  WINDOWPLACEMENT local_50;
  tagRECT local_24;
  int local_14;
  DWORD local_10;
  undefined4 local_c;
  HKEY local_8;
  
  pDVar6 = &local_10;
  phkResult = &local_8;
  lpSecurityAttributes = (LPSECURITY_ATTRIBUTES)0x0;
  samDesired = 0x20006;
  DVar5 = 0;
  lpClass = (LPWSTR)0x0;
  DVar4 = 0;
  pWVar1 = (LPCWSTR)FUN_010035fb(9);
  LVar2 = RegCreateKeyExW((HKEY)0x80000001,pWVar1,DVar4,lpClass,DVar5,samDesired,
                          lpSecurityAttributes,phkResult,pDVar6);
  if (LVar2 == 0) {
    BVar3 = IsZoomed((HWND)*param_1);
    local_14 = (-(uint)(BVar3 != 0) & 2) + 1;
    BVar3 = IsZoomed((HWND)*param_1);
    if ((BVar3 == 0) && (BVar3 = IsIconic((HWND)*param_1), BVar3 == 0)) {
      GetWindowRect((HWND)*param_1,&local_24);
    }
    else {
      local_50.length = 0x2c;
      GetWindowPlacement((HWND)*param_1,&local_50);
      local_24.left = local_50.rcNormalPosition.left;
      local_24.top = local_50.rcNormalPosition.top;
      local_24.right = local_50.rcNormalPosition.right;
      local_24.bottom = local_50.rcNormalPosition.bottom;
    }
    DVar8 = 4;
    lpData = &local_14;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(10);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,(BYTE *)lpData,DVar8);
    DVar8 = 4;
    lpData_00 = &local_24;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0xb);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,(BYTE *)lpData_00,DVar8);
    DVar8 = 4;
    lpData_01 = &local_24.top;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0xc);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,(BYTE *)lpData_01,DVar8);
    local_10 = local_24.right - local_24.left;
    DVar8 = 4;
    pDVar6 = &local_10;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0xd);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,(BYTE *)pDVar6,DVar8);
    local_10 = local_24.bottom - local_24.top;
    DVar8 = 4;
    pDVar6 = &local_10;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0xe);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,(BYTE *)pDVar6,DVar8);
    local_c = param_1[0x3d8];
    DVar8 = 4;
    pBVar7 = (BYTE *)&local_c;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x15);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,pBVar7,DVar8);
    local_c = param_1[0x3d9];
    DVar8 = 4;
    pBVar7 = (BYTE *)&local_c;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x16);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,pBVar7,DVar8);
    local_c = param_1[0x3da];
    DVar8 = 4;
    pBVar7 = (BYTE *)&local_c;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x17);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,pBVar7,DVar8);
    local_c = param_1[0x3db];
    DVar8 = 4;
    pBVar7 = (BYTE *)&local_c;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x18);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,pBVar7,DVar8);
    local_c = param_1[0x3dc];
    DVar8 = 4;
    pBVar7 = (BYTE *)&local_c;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x19);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,pBVar7,DVar8);
    local_c = param_1[0x3dd];
    DVar8 = 4;
    pBVar7 = (BYTE *)&local_c;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x33);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,pBVar7,DVar8);
    local_10 = *(DWORD *)param_1[1];
    DVar8 = 4;
    pDVar6 = &local_10;
    DVar5 = 4;
    DVar4 = 0;
    pWVar1 = (LPCWSTR)FUN_010035fb(0x31);
    RegSetValueExW(local_8,pWVar1,DVar4,DVar5,(BYTE *)pDVar6,DVar8);
    RegSetValueExW(local_8,L"HighScore_Easy",0,4,(BYTE *)(param_1 + 0x3e0),4);
    RegSetValueExW(local_8,L"Wins_Easy",0,4,(BYTE *)(param_1 + 0x3e1),4);
    RegSetValueExW(local_8,L"Losses_Easy",0,4,(BYTE *)(param_1 + 0x3e2),4);
    RegSetValueExW(local_8,L"StreakWins_Easy",0,4,(BYTE *)(param_1 + 0x3e3),4);
    RegSetValueExW(local_8,L"StreakLosses_Easy",0,4,(BYTE *)(param_1 + 0x3e4),4);
    RegSetValueExW(local_8,L"StreakCurrent_Easy",0,4,(BYTE *)(param_1 + 0x3e5),4);
    RegSetValueExW(local_8,L"FWinStreak_Easy",0,4,(BYTE *)(param_1 + 0x3e6),4);
    RegSetValueExW(local_8,L"HighScore_Medium",0,4,(BYTE *)(param_1 + 999),4);
    RegSetValueExW(local_8,L"Wins_Medium",0,4,(BYTE *)(param_1 + 1000),4);
    RegSetValueExW(local_8,L"Losses_Medium",0,4,(BYTE *)(param_1 + 0x3e9),4);
    RegSetValueExW(local_8,L"StreakWins_Medium",0,4,(BYTE *)(param_1 + 0x3ea),4);
    RegSetValueExW(local_8,L"StreakLosses_Medium",0,4,(BYTE *)(param_1 + 0x3eb),4);
    RegSetValueExW(local_8,L"StreakCurrent_Medium",0,4,(BYTE *)(param_1 + 0x3ec),4);
    RegSetValueExW(local_8,L"FWinStreak_Medium",0,4,(BYTE *)(param_1 + 0x3ed),4);
    RegSetValueExW(local_8,L"HighScore_Difficult",0,4,(BYTE *)(param_1 + 0x3ee),4);
    RegSetValueExW(local_8,L"Wins_Difficult",0,4,(BYTE *)(param_1 + 0x3ef),4);
    RegSetValueExW(local_8,L"Losses_Difficult",0,4,(BYTE *)(param_1 + 0x3f0),4);
    RegSetValueExW(local_8,L"StreakWins_Difficult",0,4,(BYTE *)(param_1 + 0x3f1),4);
    RegSetValueExW(local_8,L"StreakLosses_Difficult",0,4,(BYTE *)(param_1 + 0x3f2),4);
    RegSetValueExW(local_8,L"StreakCurrent_Difficult",0,4,(BYTE *)(param_1 + 0x3f3),4);
    RegSetValueExW(local_8,L"FWinStreak_Difficult",0,4,(BYTE *)(param_1 + 0x3f4),4);
    RegCloseKey(local_8);
    return;
  }
  return;
}



// ========================================================
// Function: FUN_010044d0 at 010044d0
// ========================================================

void __thiscall FUN_010044d0(void *this,DWORD param_1,DWORD param_2)

{
  LPCWSTR lpString2;
  WCHAR local_214 [262];
  uint local_8;
  
  local_8 = DAT_0101107c;
  SHGetSpecialFolderPathW(*(HWND *)this,local_214,5,1);
  lstrcatW(local_214,L"\\");
  lpString2 = (LPCWSTR)FUN_010035fb(0x14);
  lstrcatW(local_214,lpString2);
  CreateFileW(local_214,param_1,0,(LPSECURITY_ATTRIBUTES)0x0,param_2,0x8000000,(HANDLE)0x0);
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_0100454d at 0100454d
// ========================================================

void __fastcall FUN_0100454d(undefined4 *param_1)

{
  int iVar1;
  int *lpBuffer;
  BOOL BVar2;
  int *piVar3;
  HMENU hMenu;
  uint uVar4;
  int iVar5;
  tagRECT local_38;
  DWORD local_28;
  int local_24;
  int local_20;
  DWORD local_1c;
  int local_18;
  uint local_14;
  HANDLE local_10;
  int local_c;
  int local_8;
  
  if (param_1[0x3d5] != 0) {
    if (((param_1[0x3d7] == 0) && (param_1[0x3dc] != 0)) &&
       (iVar1 = FUN_01003627((HWND)*param_1,0x11,2,0x124), iVar1 != 6)) {
      return;
    }
    local_10 = (HANDLE)FUN_010044d0(param_1,0x80000000,3);
    if (local_10 != (HANDLE)0xffffffff) {
      local_1c = GetFileSize(local_10,(LPDWORD)0x0);
      lpBuffer = GlobalAlloc(0,local_1c);
      if ((lpBuffer != (int *)0x0) &&
         (BVar2 = ReadFile(local_10,lpBuffer,local_1c,&local_28,(LPOVERLAPPED)0x0), BVar2 != 0)) {
        iVar1 = *lpBuffer;
        if (4 < iVar1) {
          *(undefined4 *)param_1[1] = 4;
        }
        else {
          *(int *)param_1[1] = iVar1;
        }
        uVar4 = (uint)(4 >= iVar1);
        iVar1 = lpBuffer[uVar4];
        param_1[4] = iVar1;
        FUN_0100746e((void *)param_1[1],iVar1);
        *(int *)(param_1[1] + 0x10) = lpBuffer[uVar4 + 1];
        param_1[7] = lpBuffer[uVar4 + 2];
        param_1[0xd4] = lpBuffer[uVar4 + 3];
        param_1[0x16] = lpBuffer[uVar4 + 4];
        iVar5 = uVar4 + 5;
        piVar3 = param_1 + 0x3c4;
        iVar1 = 4;
        do {
          *piVar3 = lpBuffer[iVar5];
          iVar5 = iVar5 + 1;
          piVar3 = piVar3 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
        if (lpBuffer[iVar5] < 5) {
          piVar3 = param_1 + 0x3c8;
          iVar1 = 8;
          do {
            *piVar3 = lpBuffer[iVar5];
            iVar5 = iVar5 + 1;
            piVar3 = piVar3 + 1;
            iVar1 = iVar1 + -1;
          } while (iVar1 != 0);
        }
        FUN_01008042(param_1[2]);
        local_c = 0;
        do {
          local_24 = lpBuffer[iVar5];
          local_8 = 0;
          local_20 = lpBuffer[iVar5 + 1];
          iVar5 = iVar5 + 2;
          if (0 < local_24) {
            do {
              local_18 = lpBuffer[iVar5];
              iVar5 = iVar5 + 1;
              local_14 = (uint)(local_20 <= local_8);
              FUN_01008069((void *)param_1[2],local_c,local_18,local_14);
              FUN_01007400((void *)param_1[1],local_18,local_14);
              local_8 = local_8 + 1;
            } while (local_8 < local_24);
          }
          local_c = local_c + 1;
        } while (local_c < 10);
        if ((uint)(iVar5 * 4) < local_1c) {
          param_1[0x3d6] = lpBuffer[iVar5];
        }
        else {
          param_1[0x3d6] = 500;
        }
        GlobalFree(lpBuffer);
        CloseHandle(local_10);
        param_1[0x17] = 0;
        FUN_01003259(param_1);
        hMenu = GetMenu((HWND)*param_1);
        EnableMenuItem(hMenu,0x9c4b,0);
        EnableMenuItem(hMenu,0x9c46,0);
        EnableMenuItem(hMenu,0x9c4d,0);
        iVar1 = param_1[0x16];
        if (4 < iVar1) {
          EnableMenuItem(hMenu,0x9c47,1);
        }
        else {
          EnableMenuItem(hMenu,0x9c47,0);
        }
        EnableMenuItem(hMenu,0x9c50,(uint)(4 < iVar1));
        DrawMenuBar((HWND)*param_1);
        FUN_01002e98(param_1);
        param_1[0x3d7] = 0;
        InvalidateRect((HWND)*param_1,(RECT *)0x0,1);
        FUN_01003811(param_1,&local_38);
        InvalidateRect((HWND)*param_1,&local_38,0);
        return;
      }
      CloseHandle(local_10);
      if (lpBuffer != (int *)0x0) {
        GlobalFree(lpBuffer);
      }
    }
  }
  FUN_01003627((HWND)*param_1,0x12,2,0);
  return;
}



// ========================================================
// Function: FUN_010047bd at 010047bd
// ========================================================

void FUN_010047bd(HDC param_1,HDC param_2,HDC param_3,HDC param_4,int *param_5,int *param_6)

{
  int iVar1;
  DWORD DVar2;
  longlong lVar3;
  int local_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  float local_10;
  void *local_c;
  DWORD local_8;
  
  local_8 = timeGetTime();
  local_34 = *param_5;
  iStack_30 = param_5[1];
  local_10 = (float)(*param_6 - *param_5);
  iStack_2c = param_5[2];
  iStack_28 = param_5[3];
  while (DVar2 = timeGetTime(), DVar2 <= local_8 + 100) {
    local_14 = DVar2 - local_8;
    iVar1 = *param_5;
    lVar3 = __ftol();
    local_24 = (int)lVar3 + iVar1;
    local_1c = (local_24 - iVar1) + param_5[2];
    iVar1 = param_5[1];
    lVar3 = __ftol();
    local_20 = (int)lVar3 + iVar1;
    local_18 = (param_5[3] - iVar1) + local_20;
    FUN_010032d6(local_c,param_1,param_4,param_3,param_2,&local_34,&local_24);
    local_34 = local_24;
    iStack_30 = local_20;
    iStack_2c = local_1c;
    iStack_28 = local_18;
    Sleep(5);
  }
  local_24 = *param_6;
  local_20 = param_6[1];
  local_1c = param_6[2];
  local_18 = param_6[3];
  FUN_010032d6(local_c,param_1,param_4,param_3,param_2,&local_34,&local_24);
  return;
}



// ========================================================
// Function: FUN_010048c1 at 010048c1
// ========================================================

void __thiscall FUN_010048c1(void *this,int param_1)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  
  if (param_1 == 0) {
    if ((*(int *)((int)this + 0x350) == 0) && (*(int *)((int)this + 0x58) == 0)) {
      return;
    }
    bVar1 = false;
    piVar2 = (int *)((int)this + 0xf10);
    iVar3 = 4;
    do {
      if (*piVar2 < 2) {
        bVar1 = true;
      }
      piVar2 = piVar2 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    if (!bVar1) {
      return;
    }
  }
  if (**(int **)((int)this + 4) == 1) {
    iVar3 = (int)this + 0xf80;
  }
  else {
    iVar3 = (int)this + 0xf9c;
    if (**(int **)((int)this + 4) != 2) {
      iVar3 = (int)this + 0xfb8;
    }
  }
  if (param_1 == 0) {
    if (*(int *)(iVar3 + 0x18) == 0) {
      *(int *)(iVar3 + 0x14) = *(int *)(iVar3 + 0x14) + 1;
    }
    else {
      *(undefined4 *)(iVar3 + 0x18) = 0;
      *(undefined4 *)(iVar3 + 0x14) = 1;
    }
    if (*(int *)(iVar3 + 0x10) < *(int *)(iVar3 + 0x14)) {
      *(int *)(iVar3 + 0x10) = *(int *)(iVar3 + 0x14);
      goto LAB_01004960;
    }
  }
  else {
    if (*(int *)(iVar3 + 0x18) == 0) {
      *(undefined4 *)(iVar3 + 0x18) = 1;
      *(undefined4 *)(iVar3 + 0x14) = 1;
    }
    else {
      *(int *)(iVar3 + 0x14) = *(int *)(iVar3 + 0x14) + 1;
    }
    if (*(int *)(iVar3 + 0xc) < *(int *)(iVar3 + 0x14)) {
      *(int *)(iVar3 + 0xc) = *(int *)(iVar3 + 0x14);
    }
LAB_01004960:
    if (param_1 != 0) {
      *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 1;
      goto LAB_0100496d;
    }
  }
  *(int *)(iVar3 + 8) = *(int *)(iVar3 + 8) + 1;
LAB_0100496d:
  FUN_0100411f(this);
  return;
}



// ========================================================
// Function: FUN_01004a10 at 01004a10
// ========================================================

void __thiscall FUN_01004a10(void *this,HDC param_1,int param_2,int param_3)

{
  HBRUSH hbr;
  HBRUSH hbr_00;
  int mode;
  LPCWSTR pWVar1;
  int iVar2;
  tagRECT *ptVar3;
  UINT UVar4;
  tagRECT local_f8;
  COLORREF local_e8;
  tagRECT local_e4;
  void *local_d4;
  WCHAR local_d0 [100];
  uint local_8;
  
  local_8 = DAT_0101107c;
  local_d4 = this;
  FUN_01003811(this,&local_e4);
  OffsetRect(&local_e4,param_2,param_3);
  hbr = CreateSolidBrush(0x7f00);
  hbr_00 = GetStockObject(4);
  if (hbr != (HBRUSH)0x0) {
    FillRect(param_1,&local_e4,hbr);
    DeleteObject(hbr);
  }
  if (hbr_00 != (HBRUSH)0x0) {
    FrameRect(param_1,&local_e4,hbr_00);
  }
  mode = GetBkMode(param_1);
  local_e8 = GetTextColor(param_1);
  SetBkMode(param_1,1);
  SetTextColor(param_1,0xffffff);
  SetRect(&local_f8,local_e4.left + 10,local_e4.top + 0x1e,local_e4.left + 100,local_e4.top + 0x32);
  UVar4 = 0x22;
  ptVar3 = &local_f8;
  iVar2 = -1;
  pWVar1 = (LPCWSTR)FUN_010035fb(0x35);
  DrawTextW(param_1,pWVar1,iVar2,ptVar3,UVar4);
  SetRect(&local_f8,local_e4.left + 10,local_e4.top + 0x32,local_e4.left + 100,local_e4.top + 0x50);
  UVar4 = 0x22;
  ptVar3 = &local_f8;
  iVar2 = -1;
  pWVar1 = (LPCWSTR)FUN_010035fb(0x36);
  DrawTextW(param_1,pWVar1,iVar2,ptVar3,UVar4);
  wsprintfW(local_d0,L"%d",*(undefined4 *)((int)local_d4 + 0xf58));
  SetRect(&local_f8,local_e4.left + 0x6e,local_e4.top + 0x1e,local_e4.left + 200,local_e4.top + 0x32
         );
  DrawTextW(param_1,local_d0,-1,&local_f8,0x20);
  wsprintfW(local_d0,L"%d",*(undefined4 *)((int)local_d4 + 0x350));
  SetRect(&local_f8,local_e4.left + 0x6e,local_e4.top + 0x32,local_e4.left + 200,local_e4.top + 0x50
         );
  DrawTextW(param_1,local_d0,-1,&local_f8,0x20);
  SetBkMode(param_1,mode);
  SetTextColor(param_1,local_e8);
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_01004c2d at 01004c2d
// ========================================================

void __thiscall FUN_01004c2d(void *this,int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  void *pvVar2;
  bool bVar3;
  undefined3 extraout_var;
  int iVar4;
  undefined3 extraout_var_00;
  int iVar5;
  HDC hDC;
  undefined4 uVar6;
  undefined4 local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  RECT local_1c;
  int local_c;
  int local_8;
  
  local_8 = *(int *)((int)*(void **)((int)this + 8) + param_3 * 4 + 0x28) + -1;
  if (local_8 < 1) {
    local_8 = 0;
  }
  bVar3 = FUN_01007db9(*(void **)((int)this + 8),param_3);
  local_c = CONCAT31(extraout_var,bVar3);
  if ((param_4 == 0) ||
     ((0 < param_2 && (iVar4 = FUN_01002ddb(this,param_1,param_2 + -1), iVar4 == 0)))) {
    FUN_01002cf0(this,param_1,param_2,&local_1c.left);
    InvalidateRect(*(HWND *)this,&local_1c,1);
  }
  FUN_01007efa(*(void **)((int)this + 8),param_1,param_2,param_3,local_8);
  if (param_4 == 0) {
    if (param_5 != 0) {
      uVar6 = 0;
      piVar1 = (int *)(*(int *)((int)this + 8) + 0x50 + param_3 * 4);
      *piVar1 = *piVar1 + 1;
      pvVar2 = *(void **)((int)this + 4);
      iVar4 = FUN_01007ecf(*(void **)((int)this + 8),param_3,local_8);
      FUN_01007400(pvVar2,iVar4,uVar6);
    }
  }
  else {
    local_30 = 0;
    local_2c = param_1;
    local_28 = param_3;
    if (local_c == 0) {
      local_24 = local_8 + 1;
    }
    else {
      local_24 = 0;
    }
    local_20 = 0;
    bVar3 = FUN_01007db9(*(void **)((int)this + 8),param_1);
    if (CONCAT31(extraout_var_00,bVar3) == 0) {
      iVar4 = param_2 + -1;
      iVar5 = FUN_01002ddb(this,param_1,iVar4);
      if (iVar5 == 0) {
        uVar6 = 1;
        piVar1 = (int *)(*(int *)((int)this + 8) + 0x50 + param_1 * 4);
        *piVar1 = *piVar1 + -1;
        pvVar2 = *(void **)((int)this + 4);
        local_30 = 1;
        iVar5 = FUN_01007ecf(*(void **)((int)this + 8),param_1,iVar4);
        FUN_01007400(pvVar2,iVar5,uVar6);
        FUN_01002cf0(this,param_1,iVar4,&local_1c.left);
        InvalidateRect(*(HWND *)this,&local_1c,0);
      }
    }
    FUN_01003be7(this,&local_30);
  }
  FUN_01002cf0(this,param_3,local_8,&local_1c.left);
  InvalidateRect(*(HWND *)this,&local_1c,0);
  iVar4 = FUN_01002e98(this);
  if (iVar4 != 0) {
    FUN_01002cf0(this,param_3,local_8,&local_1c.left);
    local_1c.top = 0;
    local_1c.bottom = FUN_01002b1a(this);
    InvalidateRect(*(HWND *)this,&local_1c,1);
  }
  *(int *)((int)this + 0x350) = *(int *)((int)this + 0x350) + 1;
  *(undefined4 *)((int)this + 0x5c) = 0;
  FUN_01003596(this,-1);
  hDC = GetDC(*(HWND *)this);
  FUN_01004a10(this,hDC,0,0);
  ReleaseDC(*(HWND *)this,hDC);
  return;
}



// ========================================================
// Function: FUN_01004dfb at 01004dfb
// ========================================================

void __fastcall FUN_01004dfb(undefined4 *param_1)

{
  HMODULE pHVar1;
  int iVar2;
  void *this;
  DWORD DVar3;
  RECT local_18;
  HDC local_8;
  
  if (param_1[0x17] == 0) {
    FUN_01003a90(param_1);
    FUN_010031ab((int)param_1);
  }
  if (param_1[0x18] == 0) {
    if (param_1[0x3dd] != 0) {
      DVar3 = 0x40007;
      pHVar1 = GetModuleHandleW((LPCWSTR)0x0);
      PlaySoundW((LPCWSTR)0x7f,pHVar1,DVar3);
    }
  }
  else {
    local_8 = GetDC((HWND)*param_1);
    if (param_1[0x3dd] != 0) {
      DVar3 = 0x40007;
      pHVar1 = GetModuleHandleW((LPCWSTR)0x0);
      PlaySoundW((LPCWSTR)0x7e,pHVar1,DVar3);
    }
    iVar2 = FUN_0100313c((int)param_1);
    FUN_01002cf0(this,*(int *)(iVar2 + 4),*(int *)(iVar2 + 8),&local_18.left);
    InvertRect(local_8,&local_18);
    GdiFlush();
    Sleep(0xfa);
    InvertRect(local_8,&local_18);
    FUN_01002cf0(param_1,*(int *)(iVar2 + 0xc),*(int *)(iVar2 + 0x10),&local_18.left);
    InvertRect(local_8,&local_18);
    GdiFlush();
    Sleep(0xfa);
    InvertRect(local_8,&local_18);
    ReleaseDC((HWND)*param_1,local_8);
  }
  return;
}



// ========================================================
// Function: FUN_01004ef8 at 01004ef8
// ========================================================

void __fastcall FUN_01004ef8(undefined4 *param_1)

{
  int *piVar1;
  
  param_1[0x3c3] = param_1[0x3c3] + -1;
  piVar1 = param_1 + param_1[0x3c3] * 5 + 0xd5;
  if (piVar1 != (int *)0x0) {
    if (piVar1[4] == 0) {
      FUN_01004c2d(param_1,piVar1[2],piVar1[3],piVar1[1],0,*piVar1);
    }
    if (param_1[0x3c3] == 0) {
      FUN_01003259(param_1);
      return;
    }
  }
  return;
}



// ========================================================
// Function: FUN_01004f47 at 01004f47
// ========================================================

void __fastcall FUN_01004f47(undefined4 *param_1)

{
  HANDLE hObject;
  HMENU hMenu;
  
  hObject = (HANDLE)FUN_010044d0(param_1,0x80000000,3);
  hMenu = GetMenu((HWND)*param_1);
  if (hObject == (HANDLE)0xffffffff) {
    EnableMenuItem(hMenu,0x9c4c,1);
    param_1[0x3d5] = 0;
  }
  else {
    EnableMenuItem(hMenu,0x9c4c,0);
    param_1[0x3d5] = 1;
    CloseHandle(hObject);
  }
  return;
}



// ========================================================
// Function: FUN_01004fa6 at 01004fa6
// ========================================================

undefined4 __fastcall FUN_01004fa6(undefined4 *param_1)

{
  int iVar1;
  undefined4 *lpBuffer;
  undefined4 *puVar2;
  undefined4 uVar3;
  void *this;
  int iVar4;
  DWORD local_18;
  HANDLE local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar4 = 6;
  if (((param_1[0x3db] == 0) || (param_1[0x3d5] == 0)) ||
     (iVar1 = FUN_01003627((HWND)*param_1,0x10,2,0x124), iVar1 == 6)) {
    local_14 = (HANDLE)FUN_010044d0(param_1,0x40000000,2);
    if (local_14 != (HANDLE)0xffffffff) {
      lpBuffer = GlobalAlloc(0,0x800);
      if (lpBuffer != (undefined4 *)0x0) {
        *lpBuffer = *(undefined4 *)param_1[1];
        lpBuffer[1] = param_1[4];
        lpBuffer[2] = *(undefined4 *)(param_1[1] + 0x10);
        lpBuffer[3] = param_1[7];
        lpBuffer[4] = param_1[0xd4];
        lpBuffer[5] = param_1[0x16];
        puVar2 = param_1 + 0x3c4;
        iVar1 = 4;
        do {
          lpBuffer[iVar4] = *puVar2;
          iVar4 = iVar4 + 1;
          puVar2 = puVar2 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
        puVar2 = param_1 + 0x3c8;
        iVar1 = 8;
        do {
          lpBuffer[iVar4] = *puVar2;
          iVar4 = iVar4 + 1;
          puVar2 = puVar2 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
        local_c = 0;
        local_10 = 0x28;
        do {
          local_8 = 0;
          lpBuffer[iVar4] = *(undefined4 *)(local_10 + param_1[2]);
          lpBuffer[iVar4 + 1] = *(undefined4 *)(local_10 + 0x28 + param_1[2]);
          this = (void *)param_1[2];
          iVar4 = iVar4 + 2;
          if (0 < *(int *)(local_10 + (int)this)) {
            do {
              uVar3 = FUN_01007ecf(this,local_c,local_8);
              lpBuffer[iVar4] = uVar3;
              this = (void *)param_1[2];
              iVar4 = iVar4 + 1;
              local_8 = local_8 + 1;
            } while (local_8 < *(int *)(local_10 + (int)this));
          }
          local_c = local_c + 1;
          local_10 = local_10 + 4;
        } while (local_10 < 0x50);
        lpBuffer[iVar4] = param_1[0x3d6];
        WriteFile(local_14,lpBuffer,iVar4 * 4 + 4,&local_18,(LPOVERLAPPED)0x0);
        GlobalFree(lpBuffer);
        CloseHandle(local_14);
        FUN_01004f47(param_1);
        return 1;
      }
      CloseHandle(local_14);
    }
    FUN_01003627((HWND)*param_1,0x12,2,0);
  }
  return 0;
}



// ========================================================
// Function: FUN_01005115 at 01005115
// ========================================================

void __thiscall FUN_01005115(void *this,int param_1,int param_2)

{
  int iVar1;
  HDC pHVar2;
  HBITMAP pHVar3;
  HGDIOBJ pvVar4;
  uint uVar5;
  int iVar6;
  int local_4c [4];
  tagRECT local_3c;
  RECT local_2c;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = *(int *)((int)this + 4);
  *(undefined4 *)((int)this + 0x101c) = 0x47;
  *(undefined4 *)((int)this + 0x1020) = 0x60;
  GetClientRect(*(HWND *)this,&local_3c);
  iVar1 = *(int *)(iVar1 + 8) - *(int *)(iVar1 + 0x10);
  local_8 = iVar1 + 1;
  local_c = (iVar1 + 10) / 10;
  local_2c.left = FUN_01002af5(this,local_c + -1);
  local_2c.right = *(int *)((int)this + 0x101c) + local_2c.left;
  local_2c.top = local_3c.bottom + -0x6a;
  local_2c.bottom = *(int *)((int)this + 0x1020) + local_2c.top;
  local_1c = local_2c.left;
  local_18 = local_2c.top;
  local_14 = local_2c.right;
  local_10 = local_2c.bottom;
  FUN_01002c59(this,param_1,param_2,param_2,local_4c);
  pHVar2 = GetDC(*(HWND *)this);
  *(HDC *)((int)this + 0xfd4) = pHVar2;
  pHVar2 = CreateCompatibleDC(pHVar2);
  *(HDC *)((int)this + 0xfd8) = pHVar2;
  pHVar2 = CreateCompatibleDC(*(HDC *)((int)this + 0xfd4));
  *(HDC *)((int)this + 0xfdc) = pHVar2;
  pHVar2 = CreateCompatibleDC(*(HDC *)((int)this + 0xfd4));
  *(HDC *)((int)this + 0xfe0) = pHVar2;
  pHVar3 = CreateCompatibleBitmap
                     (*(HDC *)((int)this + 0xfd4),*(int *)((int)this + 0x101c),
                      *(int *)((int)this + 0x1020));
  *(HBITMAP *)((int)this + 0xfe4) = pHVar3;
  pHVar3 = CreateCompatibleBitmap
                     (*(HDC *)((int)this + 0xfd4),*(int *)((int)this + 0x101c),
                      *(int *)((int)this + 0x1020));
  *(HBITMAP *)((int)this + 0xfe8) = pHVar3;
  pHVar3 = CreateCompatibleBitmap
                     (*(HDC *)((int)this + 0xfd4),*(int *)((int)this + 0x101c),
                      *(int *)((int)this + 0x1020));
  *(HBITMAP *)((int)this + 0xfec) = pHVar3;
  pvVar4 = SelectObject(*(HDC *)((int)this + 0xfd8),*(HGDIOBJ *)((int)this + 0xfe4));
  *(HGDIOBJ *)((int)this + 0xff0) = pvVar4;
  pvVar4 = SelectObject(*(HDC *)((int)this + 0xfdc),*(HGDIOBJ *)((int)this + 0xfe8));
  *(HGDIOBJ *)((int)this + 0xff4) = pvVar4;
  pvVar4 = SelectObject(*(HDC *)((int)this + 0xfe0),*(HGDIOBJ *)((int)this + 0xfec));
  iVar6 = 1;
  iVar1 = 1;
  *(HGDIOBJ *)((int)this + 0xff8) = pvVar4;
  uVar5 = FUN_01002d16(this,param_1,param_2);
  FUN_01002899(*(HDC *)((int)this + 0xfdc),0,0,uVar5,iVar1,iVar6);
  if (local_8 % 10 == 1) {
    FUN_01002717(*(HDC *)((int)this + 0xfd8),0,0,&local_2c.left,&local_2c.left);
    if (local_c < 2) goto LAB_010052df;
    iVar1 = 0xc;
  }
  else {
    iVar1 = 0;
  }
  FUN_01002899(*(HDC *)((int)this + 0xfd8),iVar1,0,0x68,1,1);
LAB_010052df:
  FUN_010047bd(*(HDC *)((int)this + 0xfd4),*(HDC *)((int)this + 0xfdc),*(HDC *)((int)this + 0xfd8),
               *(HDC *)((int)this + 0xfe0),&local_1c,local_4c);
  SelectObject(*(HDC *)((int)this + 0xfd8),*(HGDIOBJ *)((int)this + 0xff0));
  SelectObject(*(HDC *)((int)this + 0xfdc),*(HGDIOBJ *)((int)this + 0xff4));
  SelectObject(*(HDC *)((int)this + 0xfe0),*(HGDIOBJ *)((int)this + 0xff8));
  DeleteObject(*(HGDIOBJ *)((int)this + 0xfe4));
  DeleteObject(*(HGDIOBJ *)((int)this + 0xfe8));
  DeleteObject(*(HGDIOBJ *)((int)this + 0xfec));
  DeleteDC(*(HDC *)((int)this + 0xfd8));
  DeleteDC(*(HDC *)((int)this + 0xfdc));
  DeleteDC(*(HDC *)((int)this + 0xfe0));
  ReleaseDC(*(HWND *)this,*(HDC *)((int)this + 0xfd4));
  InvalidateRect(*(HWND *)this,&local_2c,0);
  return;
}



// ========================================================
// Function: FUN_01005396 at 01005396
// ========================================================

void __thiscall FUN_01005396(void *this,HDC param_1,int param_2,int param_3)

{
  void *this_00;
  HDC hdc;
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  undefined3 extraout_var_00;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  tagRECT local_3c;
  int local_2c;
  int local_28;
  int *local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar3 = param_2;
  hdc = param_1;
  FUN_01002cf0(this,param_2,param_3,&local_2c);
  GetClientRect(*(HWND *)this,&local_3c);
  FUN_01002717(param_1,0,0,&local_3c.left,&local_2c);
  local_c = *(int *)((int)this + 0x14);
  this_00 = *(void **)((int)this + 8);
  iVar2 = *(int *)((int)this_00 + param_2 * 4 + 0x50);
  if (local_c < 0) {
    if (param_3 == 0) {
      param_1 = (HDC)0x0;
    }
    else {
      param_1 = (HDC)((param_3 - iVar2) * *(int *)((int)this + param_2 * 4 + 0x30) + iVar2 * 7);
    }
    if (0 < param_2) {
      local_14 = -0x47 - local_c;
      local_18 = *(int *)((int)this_00 + param_2 * 4 + 0x24);
      local_8 = *(int *)((int)this_00 + param_2 * 4 + 0x4c);
      bVar1 = FUN_01007db9(this_00,param_2 + -1);
      if (CONCAT31(extraout_var,bVar1) == 0) {
        param_2 = 0;
        if (0 < local_8) {
          local_10 = -(int)param_1;
          do {
            iVar5 = 1;
            iVar2 = 1;
            uVar4 = FUN_01002d16(this,iVar3 + -1,param_2);
            FUN_01002899(hdc,local_14,local_10,uVar4,iVar2,iVar5);
            param_2 = param_2 + 1;
            local_10 = local_10 + 7;
          } while (param_2 < local_8);
        }
        if (param_2 < local_18) {
          local_1c = (int *)(local_8 * 7);
          local_10 = param_2 - local_8;
          do {
            local_8 = *(int *)((int)this + iVar3 * 4 + 0x2c);
            iVar5 = 1;
            iVar2 = 1;
            uVar4 = FUN_01002d16(this,iVar3 + -1,param_2);
            FUN_01002899(hdc,local_14,(local_10 * local_8 - (int)param_1) + (int)local_1c,uVar4,
                         iVar2,iVar5);
            param_2 = param_2 + 1;
            local_10 = local_10 + 1;
          } while (param_2 < local_18);
        }
      }
      else {
        FUN_01002899(hdc,local_14,-(int)param_1,0x6c,1,1);
      }
    }
  }
  if (param_3 == 0) {
    if ((local_c < 0) && (0 < iVar3)) {
      iVar2 = SaveDC(hdc);
      ExcludeClipRect(hdc,0,0,-local_c,0x60);
      FUN_01002899(hdc,0,0,0x6c,1,1);
      RestoreDC(hdc,iVar2);
      goto LAB_01005586;
    }
    iVar6 = 1;
    iVar7 = 1;
    uVar4 = 0x6c;
    iVar5 = 0;
  }
  else {
    iVar2 = param_3 + -1;
    iVar5 = FUN_01002ddb(this,iVar3,iVar2);
    iVar6 = 1;
    iVar7 = 0;
    if (iVar5 == 0) {
      uVar4 = FUN_01002d16(this,iVar3,iVar2);
      iVar5 = -7;
    }
    else {
      iVar5 = *(int *)((int)this + iVar3 * 4 + 0x30);
      uVar4 = FUN_01002d16(this,iVar3,iVar2);
      iVar5 = -iVar5;
    }
  }
  FUN_01002899(hdc,0,iVar5,uVar4,iVar7,iVar6);
LAB_01005586:
  if ((local_c < 0) && (iVar3 < 9)) {
    iVar2 = local_c + 0x47;
    local_18 = iVar3 + 1;
    bVar1 = FUN_01007db9(*(void **)((int)this + 8),local_18);
    if (CONCAT31(extraout_var_00,bVar1) == 0) {
      local_c = *(int *)(*(int *)((int)this + 8) + 0x2c + iVar3 * 4);
      local_10 = *(int *)(*(int *)((int)this + 8) + 0x54 + iVar3 * 4);
      param_2 = 0;
      if (0 < local_10) {
        local_14 = -(int)param_1;
        do {
          iVar7 = 1;
          iVar5 = 1;
          uVar4 = FUN_01002d16(this,local_18,param_2);
          FUN_01002899(hdc,iVar2,local_14,uVar4,iVar5,iVar7);
          param_2 = param_2 + 1;
          local_14 = local_14 + 7;
        } while (param_2 < local_10);
      }
      if (param_2 < local_c) {
        local_1c = (int *)((int)this + iVar3 * 4 + 0x34);
        local_8 = local_10 * 7;
        iVar3 = param_2 - local_10;
        do {
          local_14 = *local_1c;
          iVar7 = 1;
          iVar5 = 1;
          uVar4 = FUN_01002d16(this,local_18,param_2);
          FUN_01002899(hdc,iVar2,(iVar3 * local_14 - (int)param_1) + local_8,uVar4,iVar5,iVar7);
          param_2 = param_2 + 1;
          iVar3 = iVar3 + 1;
        } while (param_2 < local_c);
      }
    }
    else {
      iVar3 = SaveDC(hdc);
      ExcludeClipRect(hdc,iVar2,0,0x47,0x60);
      FUN_01002899(hdc,iVar2,-(int)param_1,0x6c,1,1);
      RestoreDC(hdc,iVar3);
    }
  }
  iVar3 = -local_28;
  iVar2 = -local_2c;
  FUN_01004a10(this,hdc,iVar2,iVar3);
  FUN_0100385f(this,hdc,iVar2,iVar3);
  FUN_010038c3(this,hdc,iVar2,iVar3);
  return;
}



// ========================================================
// Function: FUN_01005753 at 01005753
// ========================================================

undefined4 __thiscall FUN_01005753(void *this)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  HMODULE hmod;
  HDC pHVar5;
  HBITMAP pHVar6;
  HGDIOBJ pvVar7;
  uint uVar8;
  uint in_stack_00000010;
  int iVar9;
  DWORD fdwSound;
  int local_8;
  
  uVar8 = in_stack_00000010 & 0xffff;
  uVar2 = in_stack_00000010 >> 0x10;
  if ((((*(int *)((int)this + 0x24) == 0) && (*(int *)((int)this + 0xf5c) == 0)) &&
      (iVar3 = FUN_01002b9a(this,uVar8), iVar3 != -2)) &&
     ((in_stack_00000010 = FUN_01002bcc(this,iVar3,uVar2), in_stack_00000010 != -2 &&
      (iVar4 = FUN_0100396e(this,iVar3,in_stack_00000010), iVar4 != 0)))) {
    if (*(int *)((int)this + 0xf74) != 0) {
      fdwSound = 0x40007;
      hmod = GetModuleHandleW((LPCWSTR)0x0);
      PlaySoundW((LPCWSTR)0x80,hmod,fdwSound);
    }
    SetCapture(*(HWND *)this);
    *(uint *)((int)this + 0x1030) = in_stack_00000010;
    *(int *)((int)this + 0x102c) = iVar3;
    *(undefined4 *)((int)this + 0x20) = 1;
    FUN_01002cf0(this,iVar3,in_stack_00000010,(int *)((int)this + 0xffc));
    *(int *)((int)this + 0x101c) = *(int *)((int)this + 0x1004) - *(int *)((int)this + 0xffc);
    *(int *)((int)this + 0x100c) = *(int *)((int)this + 0xffc);
    *(int *)((int)this + 0x1020) = *(int *)((int)this + 0x1008) - *(int *)((int)this + 0x1000);
    *(undefined4 *)((int)this + 0x1010) = *(undefined4 *)((int)this + 0x1000);
    *(uint *)((int)this + 0x1024) = uVar8 - *(int *)((int)this + 0xffc);
    *(undefined4 *)((int)this + 0x1014) = *(undefined4 *)((int)this + 0x1004);
    *(undefined4 *)((int)this + 0x1018) = *(undefined4 *)((int)this + 0x1008);
    *(uint *)((int)this + 0x1028) = uVar2 - *(int *)((int)this + 0x1000);
    pHVar5 = GetDC(*(HWND *)this);
    *(HDC *)((int)this + 0xfd4) = pHVar5;
    pHVar5 = CreateCompatibleDC(pHVar5);
    *(HDC *)((int)this + 0xfd8) = pHVar5;
    pHVar5 = CreateCompatibleDC(*(HDC *)((int)this + 0xfd4));
    *(HDC *)((int)this + 0xfdc) = pHVar5;
    pHVar5 = CreateCompatibleDC(*(HDC *)((int)this + 0xfd4));
    *(HDC *)((int)this + 0xfe0) = pHVar5;
    pHVar6 = CreateCompatibleBitmap
                       (*(HDC *)((int)this + 0xfd4),*(int *)((int)this + 0x101c),
                        *(int *)((int)this + 0x1020));
    *(HBITMAP *)((int)this + 0xfe4) = pHVar6;
    pHVar6 = CreateCompatibleBitmap
                       (*(HDC *)((int)this + 0xfd4),*(int *)((int)this + 0x101c),
                        *(int *)((int)this + 0x1020));
    *(HBITMAP *)((int)this + 0xfe8) = pHVar6;
    pHVar6 = CreateCompatibleBitmap
                       (*(HDC *)((int)this + 0xfd4),*(int *)((int)this + 0x101c),
                        *(int *)((int)this + 0x1020));
    *(HBITMAP *)((int)this + 0xfec) = pHVar6;
    pvVar7 = SelectObject(*(HDC *)((int)this + 0xfd8),*(HGDIOBJ *)((int)this + 0xfe4));
    *(HGDIOBJ *)((int)this + 0xff0) = pvVar7;
    pvVar7 = SelectObject(*(HDC *)((int)this + 0xfdc),*(HGDIOBJ *)((int)this + 0xfe8));
    *(HGDIOBJ *)((int)this + 0xff4) = pvVar7;
    pvVar7 = SelectObject(*(HDC *)((int)this + 0xfe0),*(HGDIOBJ *)((int)this + 0xfec));
    *(HGDIOBJ *)((int)this + 0xff8) = pvVar7;
    FUN_01005396(this,*(HDC *)((int)this + 0xfd8),iVar3,in_stack_00000010);
    iVar4 = *(int *)(*(int *)((int)this + 8) + 0x28 + iVar3 * 4);
    if ((int)in_stack_00000010 < iVar4) {
      local_8 = 0;
      do {
        iVar1 = *(int *)((int)this + iVar3 * 4 + 0x30);
        uVar8 = (uint)(in_stack_00000010 == iVar4 + -1);
        iVar9 = 1;
        uVar2 = FUN_01002d16(this,iVar3,in_stack_00000010);
        FUN_01002899(*(HDC *)((int)this + 0xfdc),0,local_8 * iVar1,uVar2,iVar9,uVar8);
        in_stack_00000010 = in_stack_00000010 + 1;
        local_8 = local_8 + 1;
      } while ((int)in_stack_00000010 < iVar4);
    }
  }
  return 0;
}



// ========================================================
// Function: FUN_010059a6 at 010059a6
// ========================================================

undefined4 __fastcall FUN_010059a6(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  BOOL BVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  tagRECT local_4c;
  RECT local_3c;
  RECT local_2c;
  RECT local_1c;
  int local_c;
  HDC local_8;
  
  if (param_1[9] != 0) {
    ReleaseCapture();
    iVar1 = param_1[5];
    if (iVar1 < 0) {
      FUN_01002c59(param_1,param_1[10],param_1[0xb],
                   *(int *)(param_1[2] + 0x28 + param_1[10] * 4) + -1,&local_3c.left);
      InvalidateRect((HWND)*param_1,&local_3c,0);
    }
    else {
      iVar6 = param_1[0xb];
      iVar2 = param_1[10];
      iVar3 = param_1[6];
      local_8 = GetDC((HWND)*param_1);
      for (; iVar6 < *(int *)(param_1[2] + 0x28 + param_1[10] * 4); iVar6 = iVar6 + 1) {
        local_c = FUN_01002ab2(param_1,param_1[10],iVar6);
        iVar8 = 1;
        iVar7 = 1;
        uVar4 = FUN_01002d16(param_1,param_1[10],iVar6);
        FUN_01002899(local_8,(iVar1 + 0x47) * iVar2 + iVar3,local_c,uVar4,iVar7,iVar8);
      }
      FUN_01002cf0(param_1,param_1[10],param_1[0xb],&local_2c.left);
      FUN_01003811(param_1,&local_4c);
      BVar5 = IntersectRect(&local_3c,&local_2c,&local_4c);
      if (BVar5 != 0) {
        FUN_01004a10(param_1,local_8,0,0);
      }
      FUN_01002b3b(param_1,&local_1c.left);
      BVar5 = IntersectRect(&local_3c,&local_2c,&local_1c);
      if (BVar5 != 0) {
        FUN_0100385f(param_1,local_8,0,0);
      }
      FUN_01003931(param_1,&local_1c.left);
      BVar5 = IntersectRect(&local_3c,&local_2c,&local_1c);
      if (BVar5 != 0) {
        FUN_010038c3(param_1,local_8,0,0);
      }
      ReleaseDC((HWND)*param_1,local_8);
    }
    param_1[9] = 0;
  }
  return 0;
}



// ========================================================
// Function: FUN_01005afb at 01005afb
// ========================================================

void __thiscall FUN_01005afb(void *this,int param_1)

{
  HMODULE hmod;
  HMENU hMenu;
  int iVar1;
  DWORD fdwSound;
  undefined4 local_c;
  undefined4 local_8;
  
  if (*(int *)((int)this + 0xf5c) == 0) {
    FUN_010048c1(this,0);
  }
  *(int *)((int)this + 0xf5c) = 0;
  *(int *)((int)this + 0x10) = param_1;
  FUN_0100746e(*(void **)((int)this + 4),param_1);
  FUN_01008042(*(int *)((int)this + 8));
  *(undefined4 *)((int)this + 0x58) = 0;
  *(undefined4 *)((int)this + 0x5c) = 0;
  *(undefined4 *)((int)this + 0x60) = 0;
  *(undefined4 *)((int)this + 100) = 0;
  FUN_01003259(this);
  *(undefined4 *)((int)this + 0x350) = 0;
  *(undefined4 *)((int)this + 0xf58) = 0;
  FUN_01003596(this,500);
  *(undefined4 *)((int)this + 0xf10) = 0;
  *(undefined4 *)((int)this + 0xf14) = 0;
  *(undefined4 *)((int)this + 0xf18) = 0;
  *(undefined4 *)((int)this + 0xf1c) = 0;
  InvalidateRect(*(HWND *)this,(RECT *)0x0,1);
  UpdateWindow(*(HWND *)this);
  param_1 = 0;
  local_c = 0;
  do {
    local_8 = 0;
    do {
      if ((local_c != 4) || (local_8 < 4)) {
        FUN_01007545(*(int *)((int)this + 4));
        FUN_01007400(*(void **)((int)this + 4),param_1,0);
        FUN_01008069(*(void **)((int)this + 8),local_8,param_1,0);
        param_1 = param_1 + 1;
      }
      local_8 = local_8 + 1;
    } while (local_8 < 10);
    local_c = local_c + 1;
  } while (local_c < 5);
  InvalidateRect(*(HWND *)this,(RECT *)0x0,1);
  if (*(int *)((int)this + 0xf60) != 0) {
    UpdateWindow(*(HWND *)this);
  }
  iVar1 = 0;
  do {
    FUN_01007545(*(int *)((int)this + 4));
    FUN_01007400(*(void **)((int)this + 4),param_1,1);
    FUN_01008069(*(void **)((int)this + 8),iVar1,param_1,1);
    if (*(int *)((int)this + 0xf60) != 0) {
      FUN_01005115(this,iVar1,(iVar1 < 4) + 4);
      if (*(int *)((int)this + 0xf74) != 0) {
        fdwSound = 0x40007;
        hmod = GetModuleHandleW((LPCWSTR)0x0);
        PlaySoundW((LPCWSTR)0x7c,hmod,fdwSound);
      }
    }
    param_1 = param_1 + 1;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 10);
  *(int *)((int)this + 0x1c) = param_1;
  hMenu = GetMenu(*(HWND *)this);
  EnableMenuItem(hMenu,0x9c46,0);
  EnableMenuItem(hMenu,0x9c47,0);
  EnableMenuItem(hMenu,0x9c50,0);
  EnableMenuItem(hMenu,0x9c4d,0);
  EnableMenuItem(hMenu,0x9c4b,0);
  DrawMenuBar(*(HWND *)this);
  return;
}



// ========================================================
// Function: FUN_01005ca9 at 01005ca9
// ========================================================

void __thiscall FUN_01005ca9(void *this,HDC param_1)

{
  int bottom;
  int iVar1;
  uint uVar2;
  int iVar3;
  wchar_t *lpBitmapName;
  tagRECT local_b8;
  HGDIOBJ local_a8;
  COLORREF local_a4;
  COLORREF local_a0;
  COLORREF local_9c;
  COLORREF local_98;
  COLORREF local_94;
  COLORREF local_90;
  COLORREF local_8c;
  COLORREF local_88;
  COLORREF local_84;
  COLORREF local_80;
  COLORREF local_7c;
  COLORREF local_78;
  HGDIOBJ local_74;
  HBITMAP local_70;
  int local_6c;
  int local_68;
  uint local_64;
  HBITMAP local_60;
  HDC local_5c;
  int local_58;
  int local_54;
  int local_50;
  HDC local_4c;
  int local_48;
  int local_44;
  undefined4 *local_40;
  uint local_3c;
  int local_38;
  int local_34;
  WCHAR local_30 [20];
  uint local_8;
  
  local_8 = DAT_0101107c;
  local_40 = this;
  GetClientRect(*(HWND *)this,&local_b8);
  FUN_01002717(param_1,0,0,&local_b8.left,&local_b8.left);
  local_5c = CreateCompatibleDC(param_1);
  local_4c = CreateCompatibleDC(param_1);
  local_70 = LoadBitmapW(DAT_01012000,L"CARDBACK");
  local_a8 = SelectObject(local_4c,local_70);
  local_50 = 0;
  local_44 = 0x50;
  do {
    local_54 = *(int *)(local_44 + -0x28 + local_40[2]);
    local_58 = *(int *)(local_44 + local_40[2]);
    iVar3 = local_40[5];
    local_34 = (iVar3 + 0x47) * local_50 + local_40[6];
    if (local_54 == 0) {
      if ((iVar3 < 0) && (0x50 < local_44)) {
        local_58 = local_40[6];
        local_3c = iVar3;
        bottom = FUN_01002b1a(local_40);
        iVar3 = local_3c + 0x47;
        uVar2 = local_50 - 1;
        iVar1 = local_3c + 0x47;
        local_3c = uVar2;
        ExcludeClipRect(param_1,iVar1 * uVar2 + local_58,0,iVar3 * uVar2 + 0x47 + local_58,bottom);
      }
      FUN_01002899(param_1,local_34,10,0x6c,1,1);
    }
    else {
      local_48 = 0;
      if (0 < local_54) {
        local_6c = -local_58;
        local_68 = 10;
        do {
          local_64 = (uint)(local_54 + -1 <= local_48);
          local_3c = FUN_01002d16(local_40,local_50,local_48);
          local_38 = local_68;
          if (local_58 <= local_48) {
            local_38 = *(int *)((int)local_40 + local_44 + -0x20) * local_6c + 10 + local_58 * 7;
          }
          local_a4 = GetPixel(param_1,local_34,local_38);
          local_a0 = GetPixel(param_1,local_34 + 1,local_38);
          local_9c = GetPixel(param_1,local_34,local_38 + 1);
          local_98 = GetPixel(param_1,local_34 + 0x46,local_38);
          local_94 = GetPixel(param_1,local_34 + 0x45,local_38);
          local_90 = GetPixel(param_1,local_34 + 0x46,local_38 + 1);
          if (local_64 != 0) {
            local_8c = GetPixel(param_1,local_34,local_38 + 0x5f);
            local_88 = GetPixel(param_1,local_34 + 1,local_38 + 0x5f);
            local_84 = GetPixel(param_1,local_34,local_38 + 0x5e);
            local_80 = GetPixel(param_1,local_34 + 0x46,local_38 + 0x5f);
            local_7c = GetPixel(param_1,local_34 + 0x45,local_38 + 0x5f);
            local_78 = GetPixel(param_1,local_34 + 0x46,local_38 + 0x5e);
          }
          if (local_3c == 0x68) {
            if (local_64 == 0) {
              iVar3 = 9;
            }
            else {
              iVar3 = 0x60;
            }
            BitBlt(param_1,local_34,local_38,0x47,iVar3,local_4c,0,0,0xcc0020);
          }
          else {
            if (((int)local_3c < 1) || (0x34 < (int)local_3c)) {
              if (local_3c == 0x69) {
                lpBitmapName = L"FELT";
              }
              else {
                lpBitmapName = (wchar_t *)(local_3c & 0xffff);
              }
            }
            else {
              wsprintfW(local_30,L"CARD%d",local_3c);
              lpBitmapName = local_30;
            }
            local_60 = LoadBitmapW(DAT_01012000,lpBitmapName);
            local_74 = SelectObject(local_5c,local_60);
            BitBlt(param_1,local_34,local_38,0x47,0x60,local_5c,0,0,0xcc0020);
            SelectObject(local_5c,local_74);
            DeleteObject(local_60);
          }
          SetPixel(param_1,local_34,local_38,local_a4);
          SetPixel(param_1,local_34 + 1,local_38,local_a0);
          SetPixel(param_1,local_34,local_38 + 1,local_9c);
          SetPixel(param_1,local_34 + 0x46,local_38,local_98);
          SetPixel(param_1,local_34 + 0x45,local_38,local_94);
          SetPixel(param_1,local_34 + 0x46,local_38 + 1,local_90);
          if (local_64 != 0) {
            SetPixel(param_1,local_34,local_38 + 0x5f,local_8c);
            SetPixel(param_1,local_34 + 1,local_38 + 0x5f,local_88);
            SetPixel(param_1,local_34,local_38 + 0x5e,local_84);
            SetPixel(param_1,local_34 + 0x46,local_38 + 0x5f,local_80);
            SetPixel(param_1,local_34 + 0x45,local_38 + 0x5f,local_7c);
            SetPixel(param_1,local_34 + 0x46,local_38 + 0x5e,local_78);
          }
          if (((0xd < (int)local_3c) && ((int)local_3c < 0x18)) ||
             ((0x1a < (int)local_3c && ((int)local_3c < 0x25)))) {
            local_3c = local_38 + 2;
            MoveToEx(param_1,local_34,local_3c,(LPPOINT)0x0);
            LineTo(param_1,local_34,local_38 + 0x5d);
            LineTo(param_1,local_34 + 2,local_38 + 0x5f);
            LineTo(param_1,local_34 + 0x44,local_38 + 0x5f);
            LineTo(param_1,local_34 + 0x46,local_38 + 0x5d);
            LineTo(param_1,local_34 + 0x46,local_3c);
            LineTo(param_1,local_34 + 0x44,local_38);
            LineTo(param_1,local_34 + 2,local_38);
            LineTo(param_1,local_34,local_3c);
          }
          local_48 = local_48 + 1;
          local_68 = local_68 + 7;
          local_6c = local_6c + 1;
        } while (local_48 < local_54);
      }
    }
    local_44 = local_44 + 4;
    local_50 = local_50 + 1;
  } while (local_44 < 0x78);
  SelectObject(local_4c,local_a8);
  DeleteObject(local_70);
  DeleteDC(local_4c);
  DeleteDC(local_5c);
  FUN_01004a10(local_40,param_1,0,0);
  FUN_0100385f(local_40,param_1,0,0);
  FUN_010038c3(local_40,param_1,0,0);
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_010061f0 at 010061f0
// ========================================================

void __fastcall FUN_010061f0(undefined4 *param_1)

{
  HMENU hMenu;
  HMODULE hmod;
  INT_PTR IVar1;
  DWORD fdwSound;
  
  param_1[0x3d7] = 1;
  hMenu = GetMenu((HWND)*param_1);
  EnableMenuItem(hMenu,0x9c4d,1);
  EnableMenuItem(hMenu,0x9c4b,1);
  FUN_010048c1(param_1,1);
  FUN_01008b21((undefined4 *)param_1[3]);
  FUN_01005ca9(param_1,*(HDC *)(param_1[3] + 0x3974));
  FUN_0100821a(param_1[3]);
  if (param_1[0x3dd] != 0) {
    fdwSound = 0x40007;
    hmod = GetModuleHandleW((LPCWSTR)0x0);
    PlaySoundW((LPCWSTR)0x81,hmod,fdwSound);
  }
  IVar1 = DialogBoxParamW(DAT_01012000,(LPCWSTR)0x82,(HWND)*param_1,FUN_01002f77,0);
  if (IVar1 == 1) {
    PostMessageW((HWND)*param_1,0x111,0x9c45,0);
  }
  return;
}



// ========================================================
// Function: FUN_010062ae at 010062ae
// ========================================================

void __thiscall FUN_010062ae(void *this,int param_1,int param_2)

{
  int iVar1;
  HDC pHVar2;
  HBITMAP pHVar3;
  HGDIOBJ pvVar4;
  uint uVar5;
  int iVar6;
  int local_24 [4];
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  *(undefined4 *)((int)this + 0x101c) = 0x47;
  *(undefined4 *)((int)this + 0x1020) = 0x60;
  iVar1 = FUN_010035e2((int)this);
  local_14 = *(int *)((int)this + 0x18) + -0xc + iVar1 * 0xc;
  local_c = local_14 + 0x47;
  local_10 = FUN_01002b1a(this);
  local_8 = *(int *)((int)this + 0x1020) + local_10;
  FUN_01002c59(this,param_1,param_2,param_2,local_24);
  pHVar2 = GetDC(*(HWND *)this);
  *(HDC *)((int)this + 0xfd4) = pHVar2;
  pHVar2 = CreateCompatibleDC(pHVar2);
  *(HDC *)((int)this + 0xfd8) = pHVar2;
  pHVar2 = CreateCompatibleDC(*(HDC *)((int)this + 0xfd4));
  *(HDC *)((int)this + 0xfdc) = pHVar2;
  pHVar2 = CreateCompatibleDC(*(HDC *)((int)this + 0xfd4));
  *(HDC *)((int)this + 0xfe0) = pHVar2;
  pHVar3 = CreateCompatibleBitmap
                     (*(HDC *)((int)this + 0xfd4),*(int *)((int)this + 0x101c),
                      *(int *)((int)this + 0x1020));
  *(HBITMAP *)((int)this + 0xfe4) = pHVar3;
  pHVar3 = CreateCompatibleBitmap
                     (*(HDC *)((int)this + 0xfd4),*(int *)((int)this + 0x101c),
                      *(int *)((int)this + 0x1020));
  *(HBITMAP *)((int)this + 0xfe8) = pHVar3;
  pHVar3 = CreateCompatibleBitmap
                     (*(HDC *)((int)this + 0xfd4),*(int *)((int)this + 0x101c),
                      *(int *)((int)this + 0x1020));
  *(HBITMAP *)((int)this + 0xfec) = pHVar3;
  pvVar4 = SelectObject(*(HDC *)((int)this + 0xfd8),*(HGDIOBJ *)((int)this + 0xfe4));
  *(HGDIOBJ *)((int)this + 0xff0) = pvVar4;
  pvVar4 = SelectObject(*(HDC *)((int)this + 0xfdc),*(HGDIOBJ *)((int)this + 0xfe8));
  *(HGDIOBJ *)((int)this + 0xff4) = pvVar4;
  pvVar4 = SelectObject(*(HDC *)((int)this + 0xfe0),*(HGDIOBJ *)((int)this + 0xfec));
  iVar6 = 1;
  iVar1 = 1;
  *(HGDIOBJ *)((int)this + 0xff8) = pvVar4;
  uVar5 = FUN_01002d16(this,param_1,param_2);
  FUN_01002899(*(HDC *)((int)this + 0xfdc),0,0,uVar5,iVar1,iVar6);
  FUN_01005396(this,*(HDC *)((int)this + 0xfd8),param_1,param_2);
  FUN_010047bd(*(HDC *)((int)this + 0xfd4),*(HDC *)((int)this + 0xfdc),*(HDC *)((int)this + 0xfd8),
               *(HDC *)((int)this + 0xfe0),local_24,&local_14);
  SelectObject(*(HDC *)((int)this + 0xfd8),*(HGDIOBJ *)((int)this + 0xff0));
  SelectObject(*(HDC *)((int)this + 0xfdc),*(HGDIOBJ *)((int)this + 0xff4));
  SelectObject(*(HDC *)((int)this + 0xfe0),*(HGDIOBJ *)((int)this + 0xff8));
  DeleteObject(*(HGDIOBJ *)((int)this + 0xfe4));
  DeleteObject(*(HGDIOBJ *)((int)this + 0xfe8));
  DeleteObject(*(HGDIOBJ *)((int)this + 0xfec));
  DeleteDC(*(HDC *)((int)this + 0xfd8));
  DeleteDC(*(HDC *)((int)this + 0xfdc));
  DeleteDC(*(HDC *)((int)this + 0xfe0));
  ReleaseDC(*(HWND *)this,*(HDC *)((int)this + 0xfd4));
  return;
}



// ========================================================
// Function: FUN_010064b9 at 010064b9
// ========================================================

void __fastcall FUN_010064b9(void *param_1)

{
  __time32_t _Var1;
  
  _Var1 = FID_conflict___time32((__time32_t *)0x0);
  FUN_01005afb(param_1,_Var1);
  return;
}



// ========================================================
// Function: FUN_010064d5 at 010064d5
// ========================================================

void __thiscall FUN_010064d5(void *this,int param_1)

{
  int *piVar1;
  void *this_00;
  bool bVar2;
  int iVar3;
  int iVar4;
  HMODULE pHVar5;
  HDC hDC;
  int iVar6;
  undefined3 extraout_var;
  DWORD DVar7;
  undefined4 uVar8;
  tagRECT local_24;
  RECT local_14;
  
  iVar6 = *(int *)(*(int *)((int)this + 8) + 0x28 + param_1 * 4);
  UpdateWindow(*(HWND *)this);
  iVar3 = FUN_01002e1a(this,param_1,iVar6 + -1);
  iVar4 = FUN_010035e2((int)this);
  *(int *)((int)this + iVar4 * 4 + 0xf20) = iVar3;
  piVar1 = (int *)((int)this + iVar3 * 4 + 0xf10);
  *piVar1 = *piVar1 + 1;
  if (*(int *)((int)this + 0xf60) == 0) {
    FUN_01002cf0(this,param_1,iVar6 + -0xd,&local_14.left);
    InvalidateRect(*(HWND *)this,&local_14,0);
    FUN_01007f80(*(void **)((int)this + 8),param_1,iVar6 + -0xd);
    if (*(int *)((int)this + 0xf74) != 0) {
      DVar7 = 0x40007;
      pHVar5 = GetModuleHandleW((LPCWSTR)0x0);
      PlaySoundW((LPCWSTR)0x7c,pHVar5,DVar7);
    }
  }
  else {
    iVar3 = iVar6 + -0xd;
    while (iVar6 = iVar6 + -1, iVar3 <= iVar6) {
      FUN_010062ae(this,param_1,iVar6);
      FUN_01007f80(*(void **)((int)this + 8),param_1,iVar6);
      if (*(int *)((int)this + 0xf74) != 0) {
        DVar7 = 0x40007;
        pHVar5 = GetModuleHandleW((LPCWSTR)0x0);
        PlaySoundW((LPCWSTR)0x7c,pHVar5,DVar7);
      }
    }
  }
  *(int *)((int)this + 0x1c) = *(int *)((int)this + 0x1c) + -0xd;
  FUN_01003259(this);
  FUN_01003596(this,100);
  FUN_01002e98(this);
  if (*(int *)((int)this + 0xf60) == 0) {
    hDC = GetDC(*(HWND *)this);
    iVar6 = FUN_01002b1a(this);
    iVar3 = FUN_010035e2((int)this);
    FUN_01002899(hDC,*(int *)((int)this + 0x18) + -0xc + iVar3 * 0xc,iVar6,
                 (*(int *)((int)this + iVar3 * 4 + 0xf1c) + 1) * 0xd,1,1);
    ReleaseDC(*(HWND *)this,hDC);
  }
  bVar2 = FUN_01007db9(*(void **)((int)this + 8),param_1);
  if (CONCAT31(extraout_var,bVar2) == 0) {
    iVar6 = *(int *)(*(int *)((int)this + 8) + 0x28 + param_1 * 4) + -1;
    iVar3 = FUN_01002ddb(this,param_1,iVar6);
    if (iVar3 == 0) {
      piVar1 = (int *)(*(int *)((int)this + 8) + 0x50 + param_1 * 4);
      *piVar1 = *piVar1 + -1;
      this_00 = *(void **)((int)this + 4);
      uVar8 = 1;
      iVar3 = FUN_01007ecf(*(void **)((int)this + 8),param_1,iVar6);
      FUN_01007400(this_00,iVar3,uVar8);
      FUN_01002cf0(this,param_1,iVar6,&local_14.left);
      InvalidateRect(*(HWND *)this,&local_14,0);
    }
  }
  FUN_01003811(this,&local_24);
  InvalidateRect(*(HWND *)this,&local_24,0);
  UpdateWindow(*(HWND *)this);
  if (*(int *)((int)this + 0x1c) < 1) {
    FUN_010061f0(this);
  }
  return;
}



// ========================================================
// Function: FUN_010066c9 at 010066c9
// ========================================================

void __fastcall FUN_010066c9(undefined4 *param_1)

{
  int iVar1;
  INT_PTR IVar2;
  
  if (((0 < (int)param_1[0xd4]) && (0 < (int)param_1[7])) && (param_1[0x3d7] == 0)) {
    iVar1 = FUN_01003627((HWND)*param_1,0x32,2,0x223);
    if (iVar1 == 2) {
      return;
    }
    if (iVar1 == 6) {
      FUN_01004fa6(param_1);
    }
  }
  IVar2 = DialogBoxParamW(DAT_01012000,(LPCWSTR)0x77,(HWND)*param_1,FUN_01007b06,(LPARAM)param_1);
  if (IVar2 == 2) {
    return;
  }
  FUN_010064b9(param_1);
  return;
}



// ========================================================
// Function: FUN_01006732 at 01006732
// ========================================================

undefined4 __thiscall
FUN_01006732(void *this,HWND param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  RECT *lprcSrc2;
  POINT pt;
  bool bVar1;
  uint uVar2;
  BOOL BVar3;
  HMODULE hmod;
  HWND pHVar4;
  undefined3 extraout_var;
  int iVar5;
  DWORD fdwSound;
  tagRECT local_48;
  RECT local_38;
  tagRECT local_28;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined1 *local_8;
  
  local_8 = (undefined1 *)(param_4 & 0xffff);
  uVar2 = param_4 >> 0x10;
  if (*(int *)((int)this + 0x20) == 0) {
    if (*(int *)((int)this + 0xf5c) == 0) {
      if (*(int *)((int)this + 0x58) < 5) {
        FUN_01002b3b(this,&local_18);
        if ((((local_18 < (int)local_8) && ((int)local_8 < local_10)) && (local_14 < (int)uVar2)) &&
           ((int)uVar2 < local_c)) {
          PostMessageW(param_1,0x111,0x9c47,0);
        }
      }
      FUN_01003811(this,&local_28);
      pt.y = uVar2;
      pt.x = (LONG)local_8;
      BVar3 = PtInRect(&local_28,pt);
      if (BVar3 != 0) {
        PostMessageW(param_1,0x111,0x9c4d,0);
      }
    }
  }
  else {
    ReleaseCapture();
    *(undefined4 *)((int)this + 0x20) = 0;
    if (*(int *)((int)this + 0xf74) != 0) {
      fdwSound = 0x40007;
      hmod = GetModuleHandleW((LPCWSTR)0x0);
      PlaySoundW((LPCWSTR)0x7d,hmod,fdwSound);
    }
    lprcSrc2 = (RECT *)((int)this + 0xffc);
    BitBlt(*(HDC *)((int)this + 0xfd4),lprcSrc2->left,*(int *)((int)this + 0x1000),
           *(int *)((int)this + 0x101c),*(int *)((int)this + 0x1020),*(HDC *)((int)this + 0xfd8),0,0
           ,0xcc0020);
    param_1 = (HWND)0xffffffff;
    pHVar4 = (HWND)FUN_01002b9a(this,lprcSrc2->left);
    local_8 = (undefined1 *)FUN_01002b9a(this,*(int *)((int)this + 0x1004));
    if ((int)local_8 < 0) {
      local_8 = (undefined1 *)((int)&pHVar4->unused + 1);
      if (8 < (int)local_8) {
        local_8 = (undefined1 *)0x9;
      }
    }
    if ((int)pHVar4 <= (int)local_8) {
      param_4 = (int)pHVar4 * 4 + 0x28;
      do {
        if (param_1 != (HWND)0xffffffff) break;
        if ((0x27 < (int)param_4) && ((int)param_4 < 0x50)) {
          FUN_01002cf0(this,(int)pHVar4,*(int *)(*(int *)((int)this + 8) + param_4) + -1,
                       &local_38.left);
          BVar3 = IntersectRect(&local_48,&local_38,lprcSrc2);
          if (BVar3 != 0) {
            bVar1 = FUN_01003a06(this,*(int *)((int)this + 0x102c),*(int *)((int)this + 0x1030),
                                 (int)pHVar4);
            if (CONCAT31(extraout_var,bVar1) != 0) {
              param_1 = pHVar4;
            }
          }
        }
        param_4 = param_4 + 4;
        pHVar4 = (HWND)((int)&pHVar4->unused + 1);
      } while ((int)pHVar4 <= (int)local_8);
    }
    pHVar4 = (HWND)0xffffffff;
    if ((int)param_1 < 0) {
      InvalidateRect(*(HWND *)this,(RECT *)((int)this + 0x100c),0);
    }
    else {
      FUN_01004c2d(this,*(int *)((int)this + 0x102c),*(int *)((int)this + 0x1030),(int)param_1,1,0);
      iVar5 = FUN_01003038(this,(int)param_1);
      if (iVar5 != 0) {
        pHVar4 = param_1;
      }
    }
    SelectObject(*(HDC *)((int)this + 0xfd8),*(HGDIOBJ *)((int)this + 0xff0));
    SelectObject(*(HDC *)((int)this + 0xfdc),*(HGDIOBJ *)((int)this + 0xff4));
    SelectObject(*(HDC *)((int)this + 0xfe0),*(HGDIOBJ *)((int)this + 0xff8));
    DeleteObject(*(HGDIOBJ *)((int)this + 0xfe4));
    DeleteObject(*(HGDIOBJ *)((int)this + 0xfe8));
    DeleteObject(*(HGDIOBJ *)((int)this + 0xfec));
    DeleteDC(*(HDC *)((int)this + 0xfd8));
    DeleteDC(*(HDC *)((int)this + 0xfdc));
    DeleteDC(*(HDC *)((int)this + 0xfe0));
    ReleaseDC(*(HWND *)this,*(HDC *)((int)this + 0xfd4));
    if (-1 < (int)pHVar4) {
      FUN_010064d5(this,(int)pHVar4);
    }
  }
  return 0;
}



// ========================================================
// Function: FUN_010069b2 at 010069b2
// ========================================================

void __fastcall FUN_010069b2(undefined4 *param_1)

{
  int iVar1;
  HMODULE pHVar2;
  uint uVar3;
  HMENU hMenu;
  int iVar4;
  int iVar5;
  UINT uIDEnableItem;
  DWORD DVar6;
  int iVar7;
  UINT uEnable;
  RECT local_2c;
  HMENU local_1c;
  int local_18;
  HDC local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((int)param_1[0x16] < 5) {
    iVar1 = FUN_01007dd3(param_1[2]);
    if (iVar1 == 0) {
      local_10 = param_1[7];
      if (param_1[0x3d8] == 0) {
        if (param_1[0x3dd] != 0) {
          DVar6 = 0x40007;
          pHVar2 = GetModuleHandleW((LPCWSTR)0x0);
          PlaySoundW((LPCWSTR)0x7c,pHVar2,DVar6);
        }
        FUN_01002b3b(param_1,&local_2c.left);
        InvalidateRect((HWND)*param_1,&local_2c,0);
      }
      local_10 = local_10 + 10;
      local_8 = 0;
      local_c = 0x28;
      do {
        iVar1 = local_c;
        local_14 = *(HDC *)(param_1[1] + 0x10);
        FUN_01007545(param_1[1]);
        FUN_01007400((void *)param_1[1],(int)local_14,1);
        FUN_01008069((void *)param_1[2],local_8,local_14,1);
        iVar1 = *(int *)(iVar1 + param_1[2]) + -1;
        if (param_1[0x3d8] == 0) {
          local_18 = FUN_01002ab2(param_1,local_8,iVar1);
          iVar4 = param_1[5];
          local_1c = (HMENU)param_1[6];
          local_14 = GetDC((HWND)*param_1);
          iVar7 = 1;
          iVar5 = 1;
          uVar3 = FUN_01002d16(param_1,local_8,iVar1);
          FUN_01002899(local_14,(int)((int)&local_1c->unused + (iVar4 + 0x47) * local_8),local_18,
                       uVar3,iVar5,iVar7);
          ReleaseDC((HWND)*param_1,local_14);
        }
        else {
          FUN_01005115(param_1,local_8,iVar1);
          if (param_1[0x3dd] != 0) {
            DVar6 = 0x40007;
            pHVar2 = GetModuleHandleW((LPCWSTR)0x0);
            PlaySoundW((LPCWSTR)0x7c,pHVar2,DVar6);
          }
          if ((int)param_1[5] < 0) {
            FUN_01002c59(param_1,local_8,iVar1,iVar1,&local_2c.left);
            InvalidateRect((HWND)*param_1,&local_2c,0);
            UpdateWindow((HWND)*param_1);
          }
        }
        local_c = local_c + 4;
        local_8 = local_8 + 1;
      } while (local_c < 0x50);
      param_1[0x16] = param_1[0x16] + 1;
      param_1[7] = local_10;
      param_1[0x17] = 0;
      param_1[0x18] = 0;
      param_1[0x19] = 0;
      FUN_01003259(param_1);
      FUN_01002e98(param_1);
      if (param_1[0x16] == 5) {
        local_1c = GetMenu((HWND)*param_1);
        uEnable = 1;
        uIDEnableItem = 0x9c47;
        hMenu = GetSubMenu(local_1c,0);
        EnableMenuItem(hMenu,uIDEnableItem,uEnable);
        EnableMenuItem(local_1c,0x9c50,1);
        DrawMenuBar((HWND)*param_1);
      }
      iVar1 = 0;
      do {
        iVar4 = FUN_01003038(param_1,iVar1);
        if (iVar4 != 0) {
          FUN_010064d5(param_1,iVar1);
          InvalidateRect((HWND)*param_1,(RECT *)0x0,0);
          UpdateWindow((HWND)*param_1);
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < 10);
    }
    else {
      FUN_01003627((HWND)*param_1,5,2,0);
    }
  }
  return;
}



// ========================================================
// Function: FUN_01006bc3 at 01006bc3
// ========================================================

void __thiscall FUN_01006bc3(void *this,HWND param_1,UINT param_2,uint param_3,LPARAM param_4)

{
  HWND pHVar1;
  HWND pHVar2;
  int iVar3;
  LPCWSTR lpString2;
  UINT Msg;
  WCHAR *pWVar4;
  WPARAM wParam;
  undefined4 uVar5;
  LPARAM lParam;
  undefined4 uVar6;
  WCHAR local_210 [260];
  uint local_8;
  
  local_8 = DAT_0101107c;
  if ((*(undefined4 **)((int)this + 0xc))[1] != 0) {
    FUN_01008281(*(undefined4 **)((int)this + 0xc));
    UpdateWindow(param_1);
  }
  pHVar2 = *(HWND *)this;
  pHVar1 = GetForegroundWindow();
  if (pHVar1 == pHVar2) {
    GetMenu(param_1);
    switch(param_3 & 0xffff) {
    case 0x9c42:
      FUN_0100327c(this);
      break;
    case 0x9c43:
      lpString2 = (LPCWSTR)FUN_010035fb(0x2b);
      lstrcpyW(local_210,lpString2);
      uVar6 = 0;
      uVar5 = 0;
      pWVar4 = local_210;
      pHVar2 = GetDesktopWindow();
      _HtmlHelpW_16(pHVar2,pWVar4,uVar5,uVar6);
      break;
    case 0x9c44:
      lParam = 0;
      wParam = 0;
      Msg = 0x10;
      goto LAB_01006d1a;
    case 0x9c45:
      if (((*(int *)((int)this + 0x350) == 0) && (*(int *)((int)this + 0x58) == 0)) ||
         ((*(int *)((int)this + 0xf5c) != 0 ||
          (iVar3 = FUN_01003627(*(HWND *)this,3,2,0x124), iVar3 == 6)))) {
        FUN_010064b9(this);
      }
      break;
    case 0x9c46:
      if (((0 < *(int *)((int)this + 0x350)) || (0 < *(int *)((int)this + 0x58))) &&
         (iVar3 = FUN_01003627(*(HWND *)this,4,2,0x124), iVar3 == 6)) {
        FUN_01005afb(this,*(int *)((int)this + 0x10));
      }
      break;
    case 0x9c47:
    case 0x9c50:
      FUN_010069b2(this);
      break;
    case 0x9c4a:
      FUN_01004ef8(this);
      break;
    case 0x9c4b:
      FUN_01004fa6(this);
      break;
    case 0x9c4c:
      FUN_0100454d(this);
      break;
    case 0x9c4d:
      FUN_01004dfb(this);
      break;
    case 0x9c4e:
      FUN_0100329a(this);
      break;
    case 0x9c4f:
      FUN_010032b8(this);
      break;
    case 0x9c51:
      FUN_010066c9(this);
    }
  }
  else {
    if ((short)param_3 != -0x63bc) {
      pHVar2 = GetForegroundWindow();
      DefWindowProcW(pHVar2,param_2,param_3,param_4);
      goto LAB_01006d62;
    }
    lParam = 0;
    wParam = 0;
    Msg = 0x10;
    param_1 = GetForegroundWindow();
LAB_01006d1a:
    SendMessageW(param_1,Msg,wParam,lParam);
  }
LAB_01006d62:
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_01006db6 at 01006db6
// ========================================================

void __thiscall FUN_01006db6(void *this,HWND param_1,uint param_2,WPARAM param_3,uint param_4)

{
  int iVar1;
  HDC pHVar2;
  BOOL BVar3;
  void *this_00;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  tagPAINTSTRUCT local_48;
  uint local_8;
  
  local_8 = DAT_0101107c;
  if (0x24 < param_2) {
    if (param_2 == 0x100) {
      if (param_3 == 0x1b) {
        ShowWindow(*(HWND *)this,6);
        goto LAB_01006e3b;
      }
    }
    else {
      if (param_2 == 0x111) {
        FUN_01006bc3(this,param_1,0x111,param_3,param_4);
        goto LAB_01006e3b;
      }
      if (param_2 == 0x200) {
        FUN_01003680(this,param_1,0x200,(byte)param_3,param_4);
        goto LAB_01006e3b;
      }
      if (param_2 == 0x201) {
        FUN_01005753(this);
        goto LAB_01006e3b;
      }
      if (param_2 == 0x202) {
        FUN_01006732(this,param_1,0x202,param_3,param_4);
        goto LAB_01006e3b;
      }
      if (param_2 == 0x204) {
        FUN_01003712(this);
        goto LAB_01006e3b;
      }
      if (param_2 == 0x205) {
        FUN_010059a6(this);
        goto LAB_01006e3b;
      }
    }
    goto LAB_01006e2f;
  }
  if (param_2 == 0x24) {
    iVar1 = GetSystemMetrics(0x20);
    iVar5 = GetSystemMetrics(0x21);
    iVar6 = GetSystemMetrics(0xf);
    iVar7 = GetSystemMetrics(4);
    *(int *)(param_4 + 0x18) = iVar1 * 2 + 600;
    *(int *)(param_4 + 0x1c) = iVar7 + 400 + iVar5 * 2 + iVar6;
    goto LAB_01006e3b;
  }
  if (param_2 == 1) {
    this_00 = (void *)FUN_0100922c((uint *)0x398c);
    if (this_00 == (void *)0x0) {
      puVar4 = (undefined4 *)0x0;
    }
    else {
      puVar4 = FUN_01008aec(this_00,param_1);
    }
    *(undefined4 **)((int)this + 0xc) = puVar4;
    goto LAB_01006e3b;
  }
  if (param_2 == 2) {
    if (*(void **)((int)this + 0xc) != (void *)0x0) {
      FUN_010026a5(*(void **)((int)this + 0xc),1);
      *(undefined4 *)((int)this + 0xc) = 0;
    }
    PostQuitMessage(0);
    goto LAB_01006e3b;
  }
  if (param_2 == 3) {
    BVar3 = IsIconic(*(HWND *)this);
    if (BVar3 != 0) {
      *(undefined4 *)((int)this + 0xf78) = 1;
    }
LAB_01006e2f:
    DefWindowProcW(param_1,param_2,param_3,param_4);
    goto LAB_01006e3b;
  }
  if (param_2 == 5) {
    iVar1 = (int)((param_4 & 0xffff) - 0x2c6) / 0xb;
    *(int *)((int)this + 0x14) = iVar1;
    if (iVar1 < 0) {
      iVar1 = 0;
    }
    *(int *)((int)this + 0x18) = iVar1;
    FUN_01002e98(this);
    if (*(int *)(*(int *)((int)this + 0xc) + 4) != 0) {
      UpdateWindow(param_1);
      FUN_01008c80(*(undefined4 **)((int)this + 0xc));
      FUN_01005ca9(this,*(HDC *)(*(int *)((int)this + 0xc) + 0x3974));
      FUN_0100821a(*(int *)((int)this + 0xc));
    }
    goto LAB_01006e3b;
  }
  if (param_2 == 0xf) {
    pHVar2 = BeginPaint(param_1,&local_48);
    if (*(int *)((int)*(void **)((int)this + 0xc) + 4) == 0) {
      FUN_01005ca9(this,pHVar2);
    }
    else {
      FUN_01008253(*(void **)((int)this + 0xc),pHVar2);
    }
    EndPaint(param_1,&local_48);
    goto LAB_01006e3b;
  }
  if (param_2 != 0x10) {
    if (param_2 == 0x1c) {
      *(WPARAM *)((int)this + 0xf7c) = param_3;
      if ((*(int *)((int)this + 0xf78) != 0) && (param_3 != 0)) {
        *(int *)((int)this + 0xf78) = 0;
      }
    }
    goto LAB_01006e2f;
  }
  FUN_0100411f(this);
  if (*(int *)((int)this + 0xf5c) == 0) {
    if (*(int *)((int)this + 0xf64) == 0) {
      iVar1 = FUN_01003627(*(HWND *)this,0x32,2,0x223);
      if (iVar1 != 6) {
        if (iVar1 != 7) goto LAB_01006e3b;
        goto LAB_01006e6e;
      }
      iVar1 = FUN_01004fa6(this);
      if (iVar1 == 0) goto LAB_01006e3b;
    }
    else {
      iVar1 = FUN_01004fa6(this);
      if (iVar1 == 0) {
LAB_01006e6e:
        FUN_010048c1(this,0);
      }
    }
  }
  DestroyWindow(param_1);
LAB_01006e3b:
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_010070ab at 010070ab
// ========================================================

void FUN_010070ab(HWND param_1,uint param_2,WPARAM param_3,uint param_4)

{
  FUN_01006db6(&DAT_01012008,param_1,param_2,param_3,param_4);
  return;
}



// ========================================================
// Function: FUN_010070c0 at 010070c0
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_010070c0(HINSTANCE param_1)

{
  int nWidth;
  LPCWSTR lpWindowName;
  LPCWSTR lpClassName;
  BOOL BVar1;
  int iVar2;
  DWORD dwStyle;
  int X;
  int Y;
  HWND hWndParent;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  WNDCLASSW local_348;
  INITCOMMONCONTROLSEX local_320;
  tagMSG local_318;
  HACCEL local_2fc;
  HWND local_2f8;
  _OSVERSIONINFOA local_2f4;
  CHAR local_260 [300];
  CHAR local_134 [300];
  uint local_8;
  
  local_8 = DAT_0101107c;
  DAT_01012000 = param_1;
  local_2f4.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_2f4);
  if (local_2f4.dwPlatformId == 1) {
    LoadStringA((HINSTANCE)0x0,0x37,local_134,300);
    LoadStringA((HINSTANCE)0x0,2,local_260,300);
    MessageBoxA((HWND)0x0,local_134,local_260,0);
  }
  else {
    local_320.dwSize = 8;
    local_320.dwICC = 8;
    InitCommonControlsEx(&local_320);
    local_348.style = 0x2003;
    local_348.lpfnWndProc = FUN_010070ab;
    local_348.cbClsExtra = 0;
    local_348.cbWndExtra = 0;
    local_348.hInstance = param_1;
    local_348.hIcon = LoadIconW(param_1,(LPCWSTR)0x67);
    local_348.hCursor = LoadCursorW((HINSTANCE)0x0,(LPCWSTR)0x7f00);
    local_348.hbrBackground = (HBRUSH)0x0;
    local_348.lpszMenuName = (LPCWSTR)0x65;
    local_348.lpszClassName = (LPCWSTR)FUN_010035fb(1);
    RegisterClassW(&local_348);
    iVar2 = -0x80000000;
    if (DAT_01012f54 == -0x80000000) {
      nWidth = -0x80000000;
    }
    else {
      nWidth = DAT_01012f54 - DAT_01012f4c;
      iVar2 = DAT_01012f58 - DAT_01012f50;
    }
    lpParam = (LPVOID)0x0;
    hMenu = (HMENU)0x0;
    hWndParent = (HWND)0x0;
    dwStyle = 0x2cf0000;
    X = DAT_01012f4c;
    Y = DAT_01012f50;
    hInstance = param_1;
    lpWindowName = (LPCWSTR)FUN_010035fb(2);
    lpClassName = (LPCWSTR)FUN_010035fb(1);
    _DAT_01012008 =
         CreateWindowExW(0,lpClassName,lpWindowName,dwStyle,X,Y,nWidth,iVar2,hWndParent,hMenu,
                         hInstance,lpParam);
    local_2f8 = _DAT_01012008;
    FUN_01004f47((undefined4 *)&DAT_01012008);
    _DAT_01012024 = 0xffffffff;
    ShowWindow(local_2f8,DAT_01012f48);
    if (DAT_01012f68 == 0) {
      UpdateWindow(local_2f8);
    }
    if ((DAT_01012f70 == 0) || (DAT_01012f5c == 0)) {
      PostMessageW(local_2f8,0x111,0x9c51,0);
    }
    else {
      local_2fc = DAT_01012f78;
      DAT_01012f78 = (HACCEL)0x0;
      FUN_0100454d((undefined4 *)&DAT_01012008);
      DAT_01012f78 = local_2fc;
    }
    local_2fc = LoadAcceleratorsW(param_1,(LPCWSTR)0x66);
    while( true ) {
      while (((DAT_01012014 != (undefined4 *)0x0 && (DAT_01012014[1] != 0)) &&
             (BVar1 = PeekMessageW(&local_318,(HWND)0x0,0,0,0), BVar1 == 0))) {
        if ((DAT_01012f80 == 0) && (DAT_01012f84 != 0)) {
          FUN_01008d21(DAT_01012014);
        }
        else {
          WaitMessage();
        }
      }
      BVar1 = GetMessageW(&local_318,(HWND)0x0,0,0);
      if (BVar1 == 0) break;
      iVar2 = _HtmlHelpW_16(0,0,0xfd,&local_318);
      if ((iVar2 == 0) &&
         ((local_318.hwnd != local_2f8 ||
          (iVar2 = TranslateAcceleratorW(local_2f8,local_2fc,&local_318), iVar2 == 0)))) {
        TranslateMessage(&local_318);
        DispatchMessageW(&local_318);
      }
    }
  }
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_010073a8 at 010073a8
// ========================================================

undefined4 * __thiscall FUN_010073a8(void *this,int param_1)

{
  undefined4 uVar1;
  
  *(undefined4 *)((int)this + 0x10) = 0;
  *(int *)((int)this + 4) = param_1;
  *(int *)((int)this + 8) = param_1 * 0x34;
  *(undefined4 *)this = 4;
  uVar1 = FUN_0100922c((uint *)(param_1 * 0x270));
  *(undefined4 *)((int)this + 0xc) = uVar1;
  return this;
}



// ========================================================
// Function: FreeValue at 010073e2
// ========================================================

/* Library Function - Single Match
    private: void __thiscall CProperty::FreeValue(void)
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

void __thiscall CProperty::FreeValue(CProperty *this)

{
  if (*(LPVOID *)(this + 0xc) != (LPVOID)0x0) {
    FUN_01009193(*(LPVOID *)(this + 0xc));
    *(undefined4 *)(this + 0xc) = 0;
  }
  return;
}



// ========================================================
// Function: FUN_01007400 at 01007400
// ========================================================

void __thiscall FUN_01007400(void *this,int param_1,undefined4 param_2)

{
  *(undefined4 *)(*(int *)((int)this + 0xc) + 8 + param_1 * 0xc) = param_2;
  return;
}



// ========================================================
// Function: FUN_0100741e at 0100741e
// ========================================================

undefined4 __thiscall FUN_0100741e(void *this,int param_1)

{
  return *(undefined4 *)(*(int *)((int)this + 0xc) + 8 + param_1 * 0xc);
}



// ========================================================
// Function: FUN_01007439 at 01007439
// ========================================================

undefined4 __thiscall FUN_01007439(void *this,int param_1)

{
  return *(undefined4 *)(*(int *)((int)this + 0xc) + param_1 * 0xc);
}



// ========================================================
// Function: FUN_01007453 at 01007453
// ========================================================

undefined4 __thiscall FUN_01007453(void *this,int param_1)

{
  return *(undefined4 *)(*(int *)((int)this + 0xc) + 4 + param_1 * 0xc);
}



// ========================================================
// Function: FUN_0100746e at 0100746e
// ========================================================

void __thiscall FUN_0100746e(void *this,int param_1)

{
  int *piVar1;
  int iVar2;
  ushort uVar3;
  undefined4 *puVar4;
  short extraout_var;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int local_8;
  
  iVar2 = *(int *)((int)this + 8);
  puVar4 = (undefined4 *)FUN_0100922c((uint *)(iVar2 << 2));
  if (puVar4 != (undefined4 *)0x0) {
    FUN_01009357(param_1);
    iVar7 = iVar2;
    puVar6 = puVar4;
    if (0 < iVar2) {
      for (; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      }
    }
    local_8 = 0;
    if (0 < *(int *)((int)this + 4)) {
      do {
        iVar7 = 0;
        do {
          param_1 = 0;
          do {
            do {
              uVar3 = FUN_0100936b();
              iVar5 = (int)(CONCAT44((int)extraout_var >> 0xf,CONCAT22(extraout_var,uVar3)) %
                           (longlong)iVar2);
            } while (puVar4[iVar5] != 0);
            puVar4[iVar5] = 1;
            piVar1 = (int *)(*(int *)((int)this + 0xc) + iVar5 * 0xc);
            *piVar1 = iVar7;
            if (*(int *)this == 1) {
              *piVar1 = 3;
            }
            else if (*(int *)this == 2) {
              if (iVar7 == 0) {
                *piVar1 = 3;
              }
              if (*piVar1 == 1) {
                *piVar1 = 2;
              }
            }
            piVar1[2] = 0;
            iVar5 = param_1 + 1;
            piVar1[1] = param_1;
            param_1 = iVar5;
          } while (iVar5 < 0xd);
          iVar7 = iVar7 + 1;
        } while (iVar7 < 4);
        local_8 = local_8 + 1;
      } while (local_8 < *(int *)((int)this + 4));
    }
    FUN_01009193(puVar4);
    *(undefined4 *)((int)this + 0x10) = 0;
  }
  return;
}



// ========================================================
// Function: FUN_01007545 at 01007545
// ========================================================

int __fastcall FUN_01007545(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(int *)(param_1 + 8) <= iVar1) {
    return 0;
  }
  *(int *)(param_1 + 0x10) = iVar1 + 1;
  return *(int *)(param_1 + 0xc) + iVar1 * 0xc;
}



// ========================================================
// Function: FUN_01007565 at 01007565
// ========================================================

void FUN_01007565(HWND param_1,int param_2,short param_3)

{
  HDC hdc;
  HDC hdc_00;
  LPCWSTR lpString2;
  HGDIOBJ pvVar1;
  INT_PTR nResult;
  tagRECT local_824;
  HGDIOBJ local_814;
  HBITMAP local_810;
  HWND local_80c;
  WCHAR local_808 [1024];
  uint local_8;
  
  local_8 = DAT_0101107c;
  local_80c = param_1;
  if (param_2 == 0xf) {
    hdc = GetDC(param_1);
    local_824.left = 0x19;
    local_824.top = 0x6e;
    local_824.right = 0x109;
    local_824.bottom = 200;
    hdc_00 = CreateCompatibleDC(hdc);
    local_810 = LoadBitmapW(DAT_01012000,(LPCWSTR)0x6a);
    local_814 = SelectObject(hdc_00,local_810);
    BitBlt(hdc,10,10,0x167,0xf2,hdc_00,0,0,0xcc0020);
    SelectObject(hdc_00,local_814);
    DeleteObject(local_810);
    DeleteDC(hdc_00);
    lpString2 = (LPCWSTR)FUN_010035fb(0xf);
    lstrcpyW(local_808,lpString2);
    pvVar1 = GetStockObject(0x11);
    pvVar1 = SelectObject(hdc,pvVar1);
    SetBkMode(hdc,1);
    DrawTextW(hdc,local_808,-1,&local_824,0x10);
    SelectObject(hdc,pvVar1);
    ReleaseDC(local_80c,hdc);
  }
  else if ((param_2 != 0x110) && (param_2 == 0x111)) {
    if (param_3 == 1) {
      nResult = 1;
    }
    else {
      if (param_3 != 2) goto LAB_010076b1;
      nResult = 2;
    }
    EndDialog(param_1,nResult);
  }
LAB_010076b1:
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_010076c2 at 010076c2
// ========================================================

void FUN_010076c2(HWND param_1,int param_2)

{
  int iVar1;
  HWND hWnd;
  LRESULT LVar2;
  LPCWSTR pWVar3;
  undefined4 uVar4;
  longlong lVar5;
  UINT UVar6;
  WCHAR local_808 [1024];
  uint local_8;
  
  local_8 = DAT_0101107c;
  if (param_2 != 0) {
    hWnd = GetDlgItem(param_1,0x3f3);
    LVar2 = SendMessageW(hWnd,0x130b,0,0);
    iVar1 = LVar2 * 0x1c + param_2;
    uVar4 = *(undefined4 *)(iVar1 + 0xf80);
    pWVar3 = (LPCWSTR)FUN_010035fb(0x21);
    wsprintfW(local_808,pWVar3,uVar4);
    SetDlgItemTextW(param_1,0x3ee,local_808);
    uVar4 = *(undefined4 *)(iVar1 + 0xf84);
    pWVar3 = (LPCWSTR)FUN_010035fb(0x22);
    wsprintfW(local_808,pWVar3,uVar4);
    SetDlgItemTextW(param_1,0x3eb,local_808);
    uVar4 = *(undefined4 *)((LVar2 + 0x8e) * 0x1c + param_2);
    pWVar3 = (LPCWSTR)FUN_010035fb(0x23);
    wsprintfW(local_808,pWVar3,uVar4);
    SetDlgItemTextW(param_1,0x3ec,local_808);
    lVar5 = __ftol();
    uVar4 = (undefined4)lVar5;
    pWVar3 = (LPCWSTR)FUN_010035fb(0x29);
    wsprintfW(local_808,pWVar3,uVar4);
    SetDlgItemTextW(param_1,0x3ed,local_808);
    uVar4 = *(undefined4 *)(iVar1 + 0xf8c);
    pWVar3 = (LPCWSTR)FUN_010035fb(0x24);
    wsprintfW(local_808,pWVar3,uVar4);
    SetDlgItemTextW(param_1,0x3ef,local_808);
    uVar4 = *(undefined4 *)(iVar1 + 0xf90);
    pWVar3 = (LPCWSTR)FUN_010035fb(0x25);
    wsprintfW(local_808,pWVar3,uVar4);
    SetDlgItemTextW(param_1,0x3f0,local_808);
    uVar4 = *(undefined4 *)(iVar1 + 0xf94);
    if (*(int *)(iVar1 + 0xf98) == 0) {
      UVar6 = 0x27;
    }
    else {
      UVar6 = 0x26;
    }
    pWVar3 = (LPCWSTR)FUN_010035fb(UVar6);
    wsprintfW(local_808,pWVar3,uVar4);
    SetDlgItemTextW(param_1,0x3f1,local_808);
  }
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_010078d9 at 010078d9
// ========================================================

void FUN_010078d9(HWND param_1,int param_2,HWND param_3,int param_4)

{
  UINT UVar1;
  LPCWSTR pWVar2;
  INT_PTR nResult;
  WCHAR local_210 [260];
  uint local_8;
  
  local_8 = DAT_0101107c;
  if (param_2 == 0x53) {
    pWVar2 = (LPCWSTR)FUN_010035fb(0x2c);
    lstrcpyW(local_210,pWVar2);
    UVar1 = 0xc;
    param_3 = *(HWND *)(param_4 + 0xc);
  }
  else {
    if (param_2 != 0x7b) {
      if (param_2 == 0x110) {
        DAT_01013040 = param_4;
        if (param_4 != 0) {
          CheckDlgButton(param_1,0x3e9,(uint)(*(int *)(param_4 + 0xf60) != 0));
          CheckDlgButton(param_1,0x3ea,(uint)(*(int *)(DAT_01013040 + 0xf64) != 0));
          CheckDlgButton(param_1,0x3eb,(uint)(*(int *)(DAT_01013040 + 0xf68) != 0));
          CheckDlgButton(param_1,0x3ec,(uint)(*(int *)(DAT_01013040 + 0xf6c) != 0));
          CheckDlgButton(param_1,0x3ed,(uint)(*(int *)(DAT_01013040 + 0xf70) != 0));
          CheckDlgButton(param_1,0x3ee,(uint)(*(int *)(DAT_01013040 + 0xf74) != 0));
        }
      }
      else if (param_2 == 0x111) {
        if (((uint)param_3 & 0xffff) == 1) {
          if (DAT_01013040 != 0) {
            UVar1 = IsDlgButtonChecked(param_1,0x3e9);
            *(uint *)(DAT_01013040 + 0xf60) = (uint)(UVar1 == 1);
            UVar1 = IsDlgButtonChecked(param_1,0x3ea);
            *(uint *)(DAT_01013040 + 0xf64) = (uint)(UVar1 == 1);
            UVar1 = IsDlgButtonChecked(param_1,0x3eb);
            *(uint *)(DAT_01013040 + 0xf68) = (uint)(UVar1 == 1);
            UVar1 = IsDlgButtonChecked(param_1,0x3ec);
            *(uint *)(DAT_01013040 + 0xf6c) = (uint)(UVar1 == 1);
            UVar1 = IsDlgButtonChecked(param_1,0x3ed);
            *(uint *)(DAT_01013040 + 0xf70) = (uint)(UVar1 == 1);
            UVar1 = IsDlgButtonChecked(param_1,0x3ee);
            *(uint *)(DAT_01013040 + 0xf74) = (uint)(UVar1 == 1);
          }
          nResult = 1;
        }
        else {
          if (((uint)param_3 & 0xffff) != 2) goto LAB_01007af2;
          nResult = 2;
        }
        EndDialog(param_1,nResult);
      }
      goto LAB_01007af2;
    }
    pWVar2 = (LPCWSTR)FUN_010035fb(0x2c);
    lstrcpyW(local_210,pWVar2);
    UVar1 = 10;
  }
  WinHelpW(param_3,local_210,UVar1,0x1011040);
LAB_01007af2:
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_01007b06 at 01007b06
// ========================================================

undefined4 FUN_01007b06(HWND param_1,int param_2,short param_3,int param_4)

{
  UINT UVar1;
  int nIDCheckButton;
  
  if (param_2 == 0x110) {
    DAT_01013044 = param_4;
    if (**(int **)(param_4 + 4) == 1) {
      nIDCheckButton = 0x3f0;
    }
    else if (**(int **)(param_4 + 4) == 2) {
      nIDCheckButton = 0x3f1;
    }
    else {
      nIDCheckButton = 0x3f2;
    }
    CheckRadioButton(param_1,0x3f0,0x3f2,nIDCheckButton);
  }
  else {
    if (param_2 != 0x111) {
      return 0;
    }
    if (param_3 == 1) {
      UVar1 = IsDlgButtonChecked(param_1,0x3f0);
      if (UVar1 == 0) {
        UVar1 = IsDlgButtonChecked(param_1,0x3f1);
        if (UVar1 == 0) {
          **(undefined4 **)(DAT_01013044 + 4) = 4;
        }
        else {
          **(undefined4 **)(DAT_01013044 + 4) = 2;
        }
      }
      else {
        **(undefined4 **)(DAT_01013044 + 4) = 1;
      }
      EndDialog(param_1,1);
    }
    else {
      if (param_3 != 2) {
        return 0;
      }
      EndDialog(param_1,2);
    }
  }
  return 1;
}



// ========================================================
// Function: FUN_01007be2 at 01007be2
// ========================================================

void FUN_01007be2(HWND param_1,int param_2,ushort param_3,int param_4)

{
  HWND hWnd;
  int iVar1;
  LRESULT LVar2;
  WPARAM wParam;
  undefined4 local_f4 [3];
  WCHAR *local_e8;
  undefined4 local_e0;
  HWND local_d8;
  HWND local_d4;
  WCHAR local_d0 [100];
  uint local_8;
  
  local_8 = DAT_0101107c;
  local_d4 = param_1;
  if (param_2 == 0x4e) {
    if (*(int *)(param_4 + 8) != -0x227) goto LAB_01007da5;
  }
  else if (param_2 == 0x110) {
    DAT_01013048 = param_4;
    local_d8 = GetDlgItem(param_1,0x3f3);
    local_e0 = 0xffffffff;
    local_f4[0] = 3;
    GetDlgItemTextW(param_1,0x3f4,local_d0,100);
    local_e8 = local_d0;
    LVar2 = SendMessageW(local_d8,0x133e,0,(LPARAM)local_f4);
    if (LVar2 == -1) goto LAB_01007da5;
    GetDlgItemTextW(local_d4,0x3f5,local_d0,100);
    local_e8 = local_d0;
    LVar2 = SendMessageW(local_d8,0x133e,1,(LPARAM)local_f4);
    if (LVar2 == -1) goto LAB_01007da5;
    GetDlgItemTextW(local_d4,0x3f6,local_d0,100);
    hWnd = local_d8;
    local_e8 = local_d0;
    LVar2 = SendMessageW(local_d8,0x133e,2,(LPARAM)local_f4);
    if (LVar2 == -1) goto LAB_01007da5;
    if (**(int **)(DAT_01013048 + 4) == 1) {
      wParam = 0;
    }
    else if (**(int **)(DAT_01013048 + 4) == 2) {
      wParam = 1;
    }
    else {
      wParam = 2;
    }
    SendMessageW(hWnd,0x130c,wParam,0);
    param_1 = local_d4;
  }
  else {
    if ((param_2 != 0x111) || (param_3 == 0)) goto LAB_01007da5;
    if (param_3 < 3) {
      EndDialog(param_1,1);
      goto LAB_01007da5;
    }
    if (((param_3 != 0x3ea) || (iVar1 = FUN_01003627(param_1,0x34,2,0x124), iVar1 != 6)) ||
       (DAT_01013048 == 0)) goto LAB_01007da5;
    FUN_01002d75(DAT_01013048);
  }
  FUN_010076c2(param_1,DAT_01013048);
LAB_01007da5:
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_01007db9 at 01007db9
// ========================================================

bool __thiscall FUN_01007db9(void *this,int param_1)

{
  return *(int *)((int)this + param_1 * 4 + 0x28) == 0;
}



// ========================================================
// Function: FUN_01007dd3 at 01007dd3
// ========================================================

undefined4 __fastcall FUN_01007dd3(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(param_1 + 0x28);
  do {
    if (*piVar1 == 0) {
      return 1;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 10);
  return 0;
}



// ========================================================
// Function: FUN_01007df2 at 01007df2
// ========================================================

void __thiscall FUN_01007df2(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)this;
  iVar2 = 0;
  if (0 < param_1) {
    do {
      if (iVar1 == 0) {
        return;
      }
      iVar1 = *(int *)(iVar1 + 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < param_1);
  }
  return;
}



// ========================================================
// Function: FUN_01007e16 at 01007e16
// ========================================================

void __thiscall FUN_01007e16(void *this,int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = FUN_01007df2(this,0);
  while ((iVar1 != 0 && (iVar1 = *(int *)(iVar1 + 8), iVar1 != 0))) {
    iVar2 = iVar2 + 1;
  }
  if (param_1 != (int *)0x0) {
    *param_1 = iVar2;
  }
  return;
}



// ========================================================
// Function: FUN_01007e47 at 01007e47
// ========================================================

undefined4 __thiscall FUN_01007e47(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  LPVOID pvVar3;
  undefined4 uVar4;
  int *extraout_ECX;
  
  pvVar3 = (LPVOID)FUN_01007df2(this,param_1);
  uVar4 = 0;
  if (pvVar3 != (LPVOID)0x0) {
    iVar1 = *(int *)((int)pvVar3 + 8);
    iVar2 = *(int *)((int)pvVar3 + 4);
    if (param_1 == 0) {
      *extraout_ECX = iVar1;
      if (iVar1 != 0) {
        *(undefined4 *)(iVar1 + 4) = 0;
      }
    }
    else {
      *(int *)(iVar2 + 8) = iVar1;
      if (iVar1 != 0) {
        *(int *)(iVar1 + 4) = iVar2;
      }
    }
    FUN_01009193(pvVar3);
    uVar4 = 1;
  }
  return uVar4;
}



// ========================================================
// Function: FUN_01007e8f at 01007e8f
// ========================================================

int __fastcall FUN_01007e8f(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)(param_1 + 0x50);
  iVar2 = 10;
  do {
    puVar1 = (undefined4 *)FUN_0100922c((uint *)0x4);
    if (puVar1 == (undefined4 *)0x0) {
      puVar1 = (undefined4 *)0x0;
    }
    else {
      *puVar1 = 0;
    }
    puVar3[-10] = 0;
    *puVar3 = 0;
    puVar3[-0x14] = puVar1;
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return param_1;
}



// ========================================================
// Function: FUN_01007ecf at 01007ecf
// ========================================================

undefined4 __thiscall FUN_01007ecf(void *this,int param_1,int param_2)

{
  void *this_00;
  undefined4 *puVar1;
  
  this_00 = *(void **)((int)this + param_1 * 4);
  if ((this_00 != (void *)0x0) &&
     (puVar1 = (undefined4 *)FUN_01007df2(this_00,param_2), puVar1 != (undefined4 *)0x0)) {
    return *puVar1;
  }
  return 0xffffffff;
}



// ========================================================
// Function: FUN_01007efa at 01007efa
// ========================================================

void __thiscall FUN_01007efa(void *this,int param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  void *this_00;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 *extraout_ECX;
  
  this_00 = *(void **)((int)this + param_1 * 4);
  piVar2 = *(int **)((int)this + param_3 * 4);
  if (((this_00 != (void *)0x0) && (piVar2 != (int *)0x0)) &&
     (iVar3 = FUN_01007df2(this_00,param_2), iVar3 != 0)) {
    if (*(int *)(iVar3 + 4) == 0) {
      *extraout_ECX = 0;
    }
    else {
      *(undefined4 *)(*(int *)(iVar3 + 4) + 8) = 0;
    }
    piVar1 = (int *)((int)this + param_3 * 4 + 0x28);
    if (*piVar1 == 0) {
      *piVar2 = iVar3;
      *(undefined4 *)(iVar3 + 4) = 0;
    }
    else {
      iVar4 = FUN_01007df2(piVar2,param_4);
      if (iVar4 != 0) {
        *(int *)(iVar4 + 8) = iVar3;
        *(int *)(iVar3 + 4) = iVar4;
      }
    }
    piVar2 = (int *)((int)this + param_1 * 4 + 0x28);
    *piVar1 = *piVar1 + (*piVar2 - param_2);
    *piVar2 = param_2;
  }
  return;
}



// ========================================================
// Function: FUN_01007f80 at 01007f80
// ========================================================

void __thiscall FUN_01007f80(void *this,int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)((int)this + param_1 * 4 + 0x28);
  iVar2 = *piVar1 + -1;
  if (param_2 <= iVar2) {
    do {
      FUN_01007e47(*(void **)((int)this + param_1 * 4),iVar2);
      iVar2 = iVar2 + -1;
    } while (param_2 <= iVar2);
  }
  *piVar1 = param_2;
  return;
}



// ========================================================
// Function: FUN_01007fb9 at 01007fb9
// ========================================================

void __fastcall FUN_01007fb9(undefined4 *param_1)

{
  int iVar1;
  
  while( true ) {
    iVar1 = FUN_01007df2(param_1,0);
    if (iVar1 == 0) break;
    FUN_01007e47(param_1,0);
  }
  *param_1 = 0;
  return;
}



// ========================================================
// Function: FUN_01007fdf at 01007fdf
// ========================================================

undefined4 __thiscall FUN_01007fdf(void *this,undefined4 *param_1,int *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if ((param_1 != (undefined4 *)0x0) &&
     (puVar2 = (undefined4 *)FUN_0100922c((uint *)0xc), puVar2 != (undefined4 *)0x0)) {
    iVar3 = FUN_01007e16(this,param_2);
    if (iVar3 == 0) {
      *(undefined4 **)this = puVar2;
    }
    else {
      *(undefined4 **)(iVar3 + 8) = puVar2;
    }
    uVar1 = *param_1;
    puVar2[2] = 0;
    *puVar2 = uVar1;
    puVar2[1] = iVar3;
    if (param_2 != (int *)0x0) {
      if (iVar3 == 0) {
        *param_2 = 0;
      }
      else {
        *param_2 = *param_2 + 1;
      }
    }
    return 1;
  }
  return 0;
}



// ========================================================
// Function: FUN_01008042 at 01008042
// ========================================================

void __fastcall FUN_01008042(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(param_1 + 0x50);
  iVar2 = 10;
  do {
    FUN_01007fb9((undefined4 *)puVar1[-0x14]);
    puVar1[-10] = 0;
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



// ========================================================
// Function: FUN_01008069 at 01008069
// ========================================================

void __thiscall FUN_01008069(void *this,int param_1,undefined4 param_2,int param_3)

{
  int *piVar1;
  void *this_00;
  int iVar2;
  int iVar3;
  undefined4 local_10 [3];
  
  iVar2 = param_1;
  this_00 = *(void **)((int)this + param_1 * 4);
  if (this_00 != (void *)0x0) {
    local_10[0] = param_2;
    iVar3 = FUN_01007fdf(this_00,local_10,&param_1);
    if ((iVar3 != 0) &&
       (piVar1 = (int *)((int)this + iVar2 * 4 + 0x28), *piVar1 = *piVar1 + 1, param_3 == 0)) {
      piVar1 = (int *)((int)this + iVar2 * 4 + 0x50);
      *piVar1 = *piVar1 + 1;
    }
  }
  return;
}



// ========================================================
// Function: FUN_010080b1 at 010080b1
// ========================================================

undefined4 * __thiscall FUN_010080b1(void *this,byte param_1)

{
  FUN_01007fb9(this);
  if ((param_1 & 1) != 0) {
    FUN_01009193(this);
  }
  return this;
}



// ========================================================
// Function: FUN_010080d7 at 010080d7
// ========================================================

void __fastcall FUN_010080d7(int param_1)

{
  void *this;
  int iVar1;
  
  iVar1 = 0;
  do {
    this = *(void **)(param_1 + iVar1 * 4);
    if (this != (void *)0x0) {
      FUN_010080b1(this,1);
    }
    *(undefined4 *)(param_1 + iVar1 * 4) = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 10);
  return;
}



// ========================================================
// Function: FUN_010080ff at 010080ff
// ========================================================

void FUN_010080ff(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = param_2[2];
  fVar2 = param_3[2];
  fVar3 = param_2[1];
  fVar4 = param_3[1];
  *param_1 = *param_2 + *param_3;
  param_1[1] = fVar3 + fVar4;
  param_1[2] = fVar1 + fVar2;
  return;
}



// ========================================================
// Function: FUN_0100812e at 0100812e
// ========================================================

void FUN_0100812e(float *param_1,float *param_2,float param_3)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_2[2];
  fVar2 = param_2[1];
  *param_1 = param_3 * *param_2;
  param_1[1] = param_3 * fVar2;
  param_1[2] = param_3 * fVar1;
  return;
}



// ========================================================
// Function: FUN_0100815b at 0100815b
// ========================================================

void FUN_0100815b(float *param_1,float param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_3[2];
  fVar2 = param_3[1];
  *param_1 = param_2 * *param_3;
  param_1[1] = param_2 * fVar2;
  param_1[2] = param_2 * fVar1;
  return;
}



// ========================================================
// Function: FUN_01008188 at 01008188
// ========================================================

void FUN_01008188(float *param_1,float *param_2,float param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = 1.0 / param_3;
  fVar1 = param_2[2];
  fVar2 = param_2[1];
  *param_1 = fVar3 * *param_2;
  param_1[1] = fVar3 * fVar2;
  param_1[2] = fVar3 * fVar1;
  return;
}



// ========================================================
// Function: FUN_010081ba at 010081ba
// ========================================================

void FUN_010081ba(void)

{
  return;
}



// ========================================================
// Function: FUN_010081e9 at 010081e9
// ========================================================

void FUN_010081e9(undefined4 param_1,undefined4 param_2,int param_3,undefined *param_4)

{
  if (-1 < param_3 + -1) {
    do {
      (*(code *)param_4)();
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}



// ========================================================
// Function: FUN_0100821a at 0100821a
// ========================================================

void __fastcall FUN_0100821a(int param_1)

{
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x14);
  BitBlt(*(HDC *)(param_1 + 0x3980),0,0,*(int *)(param_1 + 0x10),*(int *)(param_1 + 0x14),
         *(HDC *)(param_1 + 0x3974),0,0,0xcc0020);
  return;
}



// ========================================================
// Function: FUN_01008253 at 01008253
// ========================================================

void __thiscall FUN_01008253(void *this,HDC param_1)

{
  BitBlt(param_1,0,0,*(int *)((int)this + 0x10),*(int *)((int)this + 0x14),
         *(HDC *)((int)this + 0x3980),0,0,0xcc0020);
  return;
}



// ========================================================
// Function: FUN_01008281 at 01008281
// ========================================================

void __fastcall FUN_01008281(undefined4 *param_1)

{
  SelectObject((HDC)param_1[0xe5d],(HGDIOBJ)param_1[0xe5f]);
  DeleteObject((HGDIOBJ)param_1[0xe5e]);
  DeleteDC((HDC)param_1[0xe5d]);
  SelectObject((HDC)param_1[0xe60],(HGDIOBJ)param_1[0xe62]);
  SelectObject((HDC)param_1[0xe60],(HGDIOBJ)param_1[0x41]);
  DeleteObject((HGDIOBJ)param_1[0x40]);
  DeleteObject((HGDIOBJ)param_1[0xe61]);
  DeleteDC((HDC)param_1[0xe60]);
  param_1[1] = 0;
  InvalidateRect((HWND)*param_1,(RECT *)(param_1 + 2),0);
  return;
}



// ========================================================
// Function: FUN_01008309 at 01008309
// ========================================================

/* WARNING: Removing unreachable block (ram,0x01008335) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_01008309(int param_1)

{
  LPCWSTR lpString;
  float fVar1;
  DWORD DVar2;
  int iVar3;
  int iVar4;
  undefined2 unaff_DI;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  tagSIZE *psizl;
  tagRECT local_28;
  tagSIZE local_18;
  float local_10;
  float local_c;
  float local_8;
  
  DVar2 = timeGetTime();
  local_10 = (float)((DVar2 - *(int *)(param_1 + 0x3970)) % 10000) * _DAT_01001600 * _DAT_010015fc;
  FUN_010093a0((double)local_10,unaff_DI);
  lVar5 = __ftol();
  local_c = (float)lVar5;
  fVar1 = local_10 - (float)(int)local_c;
  if (local_c == 0.0) {
    local_10 = 1.0;
  }
  else {
    if (local_c != 1.4013e-45) {
      if (local_c == 2.8026e-45) {
        local_10 = 0.0;
        local_c = 1.0;
        local_8 = fVar1;
      }
      else {
        if (local_c == 4.2039e-45) {
          local_10 = 0.0;
          local_c = 1.0 - fVar1;
        }
        else {
          if (local_c != 5.60519e-45) {
            if (local_c == 7.00649e-45) {
              local_10 = 1.0;
              local_c = 0.0;
              local_8 = 1.0 - fVar1;
            }
            goto LAB_0100839f;
          }
          local_c = 0.0;
          local_10 = fVar1;
        }
        local_8 = 1.0;
      }
      goto LAB_0100839f;
    }
    local_10 = 1.0 - fVar1;
    fVar1 = 1.0;
  }
  local_8 = 0.0;
  local_c = fVar1;
LAB_0100839f:
  psizl = &local_18;
  lpString = (LPCWSTR)(param_1 + 0x38);
  iVar3 = lstrlenW(lpString);
  GetTextExtentPoint32W(*(HDC *)(param_1 + 0x3980),lpString,iVar3,psizl);
  iVar3 = *(int *)(param_1 + 0x14) - *(int *)(param_1 + 0xc);
  iVar4 = *(int *)(param_1 + 0x10) - *(int *)(param_1 + 8);
  SetRect(&local_28,(iVar4 - local_18.cx) / 2,(iVar3 - local_18.cy) / 2,(local_18.cx + iVar4) / 2,
          (local_18.cy + iVar3) / 2);
  lVar5 = __ftol();
  lVar6 = __ftol();
  lVar7 = __ftol();
  SetTextColor(*(HDC *)(param_1 + 0x3980),
               (uint)CONCAT11((char)lVar5,(char)lVar6) << 8 | (uint)lVar7 & 0xff);
  SetBkMode(*(HDC *)(param_1 + 0x3980),1);
  DrawTextW(*(HDC *)(param_1 + 0x3980),lpString,-1,&local_28,0x25);
  UnionRect((LPRECT)(param_1 + 0x28),(LPRECT)(param_1 + 0x28),&local_28);
  return;
}



// ========================================================
// Function: FUN_010084c1 at 010084c1
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_010084c1(int param_1)

{
  ushort uVar1;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  float *pfVar2;
  float *pfVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 uVar4;
  float *pfVar5;
  float10 fVar6;
  float fVar7;
  float local_c8 [3];
  float local_bc [3];
  float local_b0 [3];
  float local_a4 [3];
  float local_98 [3];
  float local_8c [3];
  float local_80 [3];
  float local_74 [3];
  float local_68 [3];
  float local_5c [3];
  float local_50;
  float fStack_4c;
  float fStack_48;
  float local_44;
  float fStack_40;
  float fStack_3c;
  float local_38;
  float fStack_34;
  float fStack_30;
  float local_2c;
  float fStack_28;
  float fStack_24;
  float local_20 [3];
  int local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_10 = (float)timeGetTime();
  fVar7 = (float)(int)local_10;
  if ((int)local_10 < 0) {
    fVar7 = fVar7 + _DAT_010015e4;
  }
  fVar7 = fVar7 * _DAT_01001624;
  *(undefined4 *)(param_1 + 0x1c30) = 0;
  local_20[0] = 0.0;
  local_20[1] = -6.8;
  pfVar5 = (float *)(param_1 + 0x18);
  local_20[2] = 0.0;
  local_14 = 100;
  local_c = (fVar7 - *(float *)(param_1 + 0x1c20)) - _DAT_01001620;
  uVar4 = extraout_ECX;
  do {
    if (_DAT_01002568 <= local_c) {
      local_38 = pfVar5[3];
      fStack_34 = pfVar5[4];
      fStack_30 = pfVar5[5];
      local_50 = *pfVar5;
      fStack_4c = pfVar5[1];
      fStack_48 = pfVar5[2];
      fVar6 = (float10)FUN_0100950c(uVar4);
      pfVar2 = local_20;
      fVar7 = (float)(((float10)_DAT_01001620 - fVar6) * (float10)_DAT_0100160c);
      pfVar3 = (float *)FUN_0100815b(local_8c,_DAT_01001608,&local_38);
      pfVar2 = (float *)FUN_010080ff(local_bc,pfVar3,pfVar2);
      pfVar2 = (float *)FUN_0100812e(local_68,pfVar2,fVar7);
      fVar7 = _DAT_01001608;
      pfVar3 = (float *)FUN_0100812e(local_80,local_20,local_c);
      pfVar3 = (float *)FUN_01008188(local_98,pfVar3,fVar7);
      pfVar3 = (float *)FUN_010080ff(local_b0,&local_50,pfVar3);
      pfVar2 = (float *)FUN_010080ff(local_c8,pfVar3,pfVar2);
      local_10 = local_c / pfVar5[9];
      pfVar5[-6] = *pfVar2;
      pfVar5[-5] = pfVar2[1];
      pfVar5[-4] = pfVar2[2];
      pfVar5[10] = local_10;
      local_8 = local_10;
      fVar6 = (float10)FUN_0100950c(extraout_ECX_01);
      pfVar5[6] = (float)fVar6;
      fVar6 = (float10)FUN_0100950c(extraout_ECX_02);
      pfVar5[7] = (float)fVar6;
      fVar6 = (float10)FUN_0100950c(extraout_ECX_03);
      pfVar5[8] = (float)fVar6;
      fVar6 = (float10)FUN_0100950c(extraout_ECX_04);
      pfVar5[0xb] = (float)fVar6;
      uVar4 = extraout_ECX_05;
      if (_DAT_01001620 <= local_10) {
        *(int *)(param_1 + 0x1c30) = *(int *)(param_1 + 0x1c30) + 1;
      }
    }
    else {
      local_44 = pfVar5[-3];
      fStack_40 = pfVar5[-2];
      fStack_3c = pfVar5[-1];
      local_2c = *pfVar5;
      fStack_28 = pfVar5[1];
      fStack_24 = pfVar5[2];
      fVar7 = _DAT_0100161c;
      uVar1 = FUN_0100936b();
      local_8 = (float)CONCAT22(extraout_var,uVar1);
      local_10 = (float)(int)local_8;
      uVar1 = FUN_0100936b();
      local_8 = (float)CONCAT22(extraout_var_00,uVar1);
      pfVar2 = (float *)FUN_0100812e(local_5c,&local_44,
                                     local_c - ((local_10 - (float)(int)local_8) * _DAT_01001618 +
                                               _DAT_01001620) * _DAT_01001614);
      pfVar2 = (float *)FUN_01008188(local_74,pfVar2,fVar7);
      pfVar2 = (float *)FUN_010080ff(local_a4,&local_2c,pfVar2);
      pfVar5[-6] = *pfVar2;
      pfVar5[-5] = pfVar2[1];
      pfVar5[-4] = pfVar2[2];
      uVar4 = extraout_ECX_00;
    }
    pfVar5 = pfVar5 + 0x12;
    local_14 = local_14 + -1;
  } while (local_14 != 0);
  return;
}



// ========================================================
// Function: FUN_01008700 at 01008700
// ========================================================

void __fastcall FUN_01008700(int param_1)

{
  HBRUSH h;
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  HGDIOBJ pvStack00000004;
  tagRECT local_20;
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = *(int *)(param_1 + 8);
  iVar3 = *(int *)(param_1 + 0x14) - *(int *)(param_1 + 0xc);
  iVar1 = *(int *)(param_1 + 0x10) - local_10;
  local_c = iVar3;
  if (iVar1 <= iVar3) {
    local_c = iVar1;
  }
  local_c = local_c / 0x32;
  local_8 = param_1;
  lVar4 = __ftol();
  iVar2 = iVar1 / 2 + (int)lVar4 + local_10;
  lVar4 = __ftol();
  iVar3 = (iVar3 / -2 - (int)lVar4) + *(int *)(local_8 + 0x14);
  lVar4 = __ftol();
  iVar1 = (int)lVar4 / 2;
  SetRect(&local_20,iVar2 - iVar1,iVar3 - iVar1,iVar1 + iVar2,iVar1 + iVar3);
  lVar4 = __ftol();
  lVar5 = __ftol();
  lVar6 = __ftol();
  h = CreateSolidBrush((uint)CONCAT11((char)lVar4,(char)lVar5) << 8 | (uint)lVar6 & 0xff);
  iVar1 = local_8;
  pvStack00000004 = SelectObject(*(HDC *)(local_8 + 0x3980),h);
  Ellipse(*(HDC *)(iVar1 + 0x3980),local_20.left,local_20.top,local_20.right,local_20.bottom);
  SelectObject(*(HDC *)(iVar1 + 0x3980),pvStack00000004);
  DeleteObject(h);
  UnionRect((LPRECT)(iVar1 + 0x28),(LPRECT)(iVar1 + 0x28),&local_20);
  return;
}



// ========================================================
// Function: FUN_0100882d at 0100882d
// ========================================================

float10 FUN_0100882d(void)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_010081ba();
  return SQRT(fVar1);
}



// ========================================================
// Function: FUN_01008845 at 01008845
// ========================================================

float * FUN_01008845(float *param_1,float *param_2)

{
  float10 fVar1;
  
  fVar1 = FUN_0100882d();
  FUN_01008188(param_1,param_2,(float)fVar1);
  return param_1;
}



// ========================================================
// Function: FUN_0100888a at 0100888a
// ========================================================

void __fastcall FUN_0100888a(undefined4 *param_1)

{
  if (param_1[1] != 0) {
    FUN_01008281(param_1);
    return;
  }
  return;
}



// ========================================================
// Function: FUN_0100889b at 0100889b
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0100889b(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  ushort uVar5;
  ushort uVar6;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  short extraout_var_02;
  short extraout_var_03;
  short extraout_var_04;
  undefined2 extraout_var_05;
  undefined2 extraout_var_06;
  undefined2 extraout_var_07;
  undefined2 extraout_var_08;
  undefined2 extraout_var_09;
  undefined2 extraout_var_10;
  float *pfVar7;
  undefined4 *puVar8;
  undefined2 extraout_var_11;
  undefined2 extraout_var_12;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  float local_6c [3];
  float local_60 [3];
  float local_54 [3];
  float local_48;
  float local_44;
  float local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  uVar5 = FUN_0100936b();
  local_8 = (float)CONCAT22(extraout_var,uVar5);
  local_c = (float)(int)local_8;
  uVar5 = FUN_0100936b();
  local_8 = (float)CONCAT22(extraout_var_00,uVar5);
  local_20 = 0x41f00000;
  local_24 = (local_c - (float)(int)local_8) * _DAT_01001618 * _DAT_01001644;
  local_1c = 0;
  uVar5 = FUN_0100936b();
  local_c = (float)CONCAT22(extraout_var_01,uVar5);
  local_18 = (float)(int)local_c * _DAT_01001618 * _DAT_01001640 + _DAT_01001644;
  local_14 = (float)timeGetTime();
  fVar1 = (float)(int)local_14;
  if ((int)local_14 < 0) {
    fVar1 = fVar1 + _DAT_010015e4;
  }
  *(float *)(param_1 + 0x1c20) = fVar1 * _DAT_01001624;
  uVar5 = FUN_0100936b();
  uVar6 = FUN_0100936b();
  iVar9 = (int)(CONCAT44((int)extraout_var_03 >> 0xf,CONCAT22(extraout_var_03,uVar6)) % 2);
  uVar6 = FUN_0100936b();
  uVar3 = _DAT_0100163c;
  uVar4 = _DAT_01001638;
  iVar10 = (int)(CONCAT44((int)extraout_var_04 >> 0xf,CONCAT22(extraout_var_04,uVar6)) % 2);
  uVar2 = _DAT_01001638;
  if (((int)(CONCAT44((int)extraout_var_02 >> 0xf,CONCAT22(extraout_var_02,uVar5)) % 2) == 0) &&
     (uVar2 = _DAT_0100163c, iVar9 == 0)) {
    iVar10 = 1;
  }
  *(undefined4 *)(param_1 + 0x1c24) = uVar2;
  if (iVar9 == 0) {
    uVar4 = uVar3;
  }
  *(undefined4 *)(param_1 + 0x1c28) = uVar4;
  if (iVar10 != 0) {
    uVar3 = _DAT_01001638;
  }
  *(undefined4 *)(param_1 + 0x1c2c) = uVar3;
  puVar11 = (undefined4 *)(param_1 + 0x18);
  param_1 = 100;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  do {
    puVar11[-6] = local_30;
    puVar11[-5] = local_2c;
    puVar11[-4] = local_28;
    puVar11[-3] = local_24;
    puVar11[-2] = local_20;
    puVar11[-1] = local_1c;
    *puVar11 = local_3c;
    puVar11[1] = local_38;
    puVar11[2] = local_34;
    uVar5 = FUN_0100936b();
    local_c = (float)CONCAT22(extraout_var_05,uVar5);
    local_8 = (float)(int)local_c;
    uVar5 = FUN_0100936b();
    local_c = (float)CONCAT22(extraout_var_06,uVar5);
    local_14 = (local_8 - (float)(int)local_c) * _DAT_01001618;
    uVar5 = FUN_0100936b();
    local_c = (float)CONCAT22(extraout_var_07,uVar5);
    local_8 = (float)(int)local_c;
    uVar5 = FUN_0100936b();
    local_c = (float)CONCAT22(extraout_var_08,uVar5);
    local_10 = (local_8 - (float)(int)local_c) * _DAT_01001618;
    uVar5 = FUN_0100936b();
    local_c = (float)CONCAT22(extraout_var_09,uVar5);
    local_8 = (float)(int)local_c;
    uVar5 = FUN_0100936b();
    local_c = (float)CONCAT22(extraout_var_10,uVar5);
    local_44 = local_10;
    local_40 = local_14;
    local_48 = (local_8 - (float)(int)local_c) * _DAT_01001618;
    pfVar7 = FUN_01008845(local_54,&local_48);
    pfVar7 = (float *)FUN_0100815b(local_60,local_18,pfVar7);
    puVar8 = (undefined4 *)FUN_010080ff(local_6c,&local_24,pfVar7);
    uVar2 = _DAT_01001634;
    puVar11[3] = *puVar8;
    puVar11[4] = puVar8[1];
    puVar11[5] = puVar8[2];
    puVar11[8] = uVar2;
    puVar11[7] = uVar2;
    puVar11[6] = uVar2;
    uVar5 = FUN_0100936b();
    local_14 = (float)CONCAT22(extraout_var_11,uVar5);
    local_10 = (float)(int)local_14;
    uVar5 = FUN_0100936b();
    local_14 = (float)CONCAT22(extraout_var_12,uVar5);
    puVar11[0xb] = 0x3e4ccccd;
    param_1 = param_1 + -1;
    puVar11[9] = ((local_10 - (float)(int)local_14) * _DAT_01001618 * _DAT_01001630 + _DAT_01001620)
                 * _DAT_0100162c;
    puVar11[10] = 0;
    puVar11 = puVar11 + 0x12;
  } while (param_1 != 0);
  return;
}



// ========================================================
// Function: FUN_01008aec at 01008aec
// ========================================================

undefined4 * __thiscall FUN_01008aec(void *this,undefined4 param_1)

{
  FUN_010081e9((int)this + 0x108,0x1c34,2,&LAB_0100886d);
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)this = param_1;
  return this;
}



// ========================================================
// Function: FUN_01008b21 at 01008b21
// ========================================================

void __fastcall FUN_01008b21(undefined4 *param_1)

{
  HDC hdc;
  HDC pHVar1;
  HBITMAP pHVar2;
  HGDIOBJ pvVar3;
  HFONT h;
  DWORD DVar4;
  int iVar5;
  LOGFONTW *pLVar6;
  int nDenominator;
  LOGFONTW local_64;
  uint local_8;
  
  local_8 = DAT_0101107c;
  param_1[1] = 1;
  GetClientRect((HWND)*param_1,(LPRECT)(param_1 + 2));
  hdc = GetDC((HWND)*param_1);
  pHVar1 = CreateCompatibleDC(hdc);
  param_1[0xe5d] = pHVar1;
  pHVar2 = CreateCompatibleBitmap(hdc,param_1[4],param_1[5]);
  param_1[0xe5e] = pHVar2;
  pvVar3 = SelectObject((HDC)param_1[0xe5d],pHVar2);
  param_1[0xe5f] = pvVar3;
  pHVar1 = CreateCompatibleDC(hdc);
  param_1[0xe60] = pHVar1;
  pHVar2 = CreateCompatibleBitmap(hdc,param_1[4],param_1[5]);
  param_1[0xe61] = pHVar2;
  pvVar3 = SelectObject((HDC)param_1[0xe60],pHVar2);
  nDenominator = 0x48;
  pHVar1 = (HDC)param_1[0xe60];
  param_1[0xe62] = pvVar3;
  pLVar6 = &local_64;
  for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1) {
    pLVar6->lfHeight = 0;
    pLVar6 = (LOGFONTW *)&pLVar6->lfWidth;
  }
  iVar5 = GetDeviceCaps(pHVar1,0x5a);
  local_64.lfHeight = MulDiv(0x30,iVar5,nDenominator);
  local_64.lfHeight = -local_64.lfHeight;
  local_64.lfWeight = 800;
  local_64.lfCharSet = '\x01';
  LoadStringW((HINSTANCE)0x0,0x30,local_64.lfFaceName,0x20);
  h = CreateFontIndirectW(&local_64);
  param_1[0x40] = h;
  pvVar3 = SelectObject((HDC)param_1[0xe60],h);
  param_1[0x41] = pvVar3;
  FUN_0100889b((int)(param_1 + 0x42));
  FUN_0100889b((int)(param_1 + 0x74f));
  ReleaseDC((HWND)*param_1,hdc);
  DVar4 = timeGetTime();
  param_1[0xe5c] = DVar4;
  SetRect((LPRECT)(param_1 + 6),0,0,0,0);
  LoadStringW((HINSTANCE)0x0,0x2d,(LPWSTR)(param_1 + 0xe),100);
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_01008c80 at 01008c80
// ========================================================

void __fastcall FUN_01008c80(undefined4 *param_1)

{
  FUN_01008281(param_1);
  FUN_01008b21(param_1);
  return;
}



// ========================================================
// Function: FUN_01008c97 at 01008c97
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_01008c97(void *this,int param_1)

{
  float fVar1;
  DWORD DVar2;
  int iVar3;
  int iVar4;
  
  DVar2 = timeGetTime();
  fVar1 = (float)(int)DVar2;
  if ((int)DVar2 < 0) {
    fVar1 = fVar1 + _DAT_010015e4;
  }
  fVar1 = fVar1 * _DAT_01001624;
  if (*(float *)(param_1 + 0x1c20) <= fVar1) {
    iVar3 = 100;
    iVar4 = param_1;
    do {
      if (*(float *)(iVar4 + 0x40) < _DAT_01001620) {
        FUN_01008700((int)this);
      }
      iVar4 = iVar4 + 0x48;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    if (*(int *)(param_1 + 0x1c30) == 100) {
      *(float *)(param_1 + 0x1c20) = fVar1;
      FUN_0100889b(param_1);
    }
  }
  return;
}



// ========================================================
// Function: FUN_01008d21 at 01008d21
// ========================================================

void __fastcall FUN_01008d21(undefined4 *param_1)

{
  int x;
  HDC hdc;
  undefined4 *puVar1;
  int iVar2;
  tagRECT local_14;
  
  iVar2 = param_1[0xb];
  x = param_1[10];
  BitBlt((HDC)param_1[0xe60],x,iVar2,param_1[0xc] - x,param_1[0xd] - iVar2,(HDC)param_1[0xe5d],x,
         iVar2,0xcc0020);
  param_1[6] = param_1[10];
  param_1[7] = param_1[0xb];
  param_1[8] = param_1[0xc];
  param_1[9] = param_1[0xd];
  SetRect((LPRECT)(param_1 + 10),0,0,0,0);
  FUN_01008309((int)param_1);
  puVar1 = param_1 + 0x42;
  iVar2 = 2;
  do {
    FUN_010084c1((int)puVar1);
    FUN_01008c97(param_1,(int)puVar1);
    puVar1 = puVar1 + 0x70d;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  UnionRect(&local_14,(RECT *)(param_1 + 6),(RECT *)(param_1 + 10));
  hdc = GetDC((HWND)*param_1);
  BitBlt(hdc,local_14.left,local_14.top,local_14.right - local_14.left,
         local_14.bottom - local_14.top,(HDC)param_1[0xe60],local_14.left,local_14.top,0xcc0020);
  ReleaseDC((HWND)*param_1,hdc);
  return;
}



// ========================================================
// Function: ___security_init_cookie at 01008df8
// ========================================================

/* Library Function - Single Match
    ___security_init_cookie
   
   Library: Visual Studio 2005 Release */

void __cdecl ___security_init_cookie(void)

{
  DWORD DVar1;
  DWORD DVar2;
  DWORD DVar3;
  LARGE_INTEGER local_14;
  _FILETIME local_c;
  
  if ((DAT_0101107c == 0) || (DAT_0101107c == 0xbb40)) {
    GetSystemTimeAsFileTime(&local_c);
    DVar1 = GetCurrentProcessId();
    DVar2 = GetCurrentThreadId();
    DVar3 = GetTickCount();
    QueryPerformanceCounter(&local_14);
    DAT_0101107c = (local_14.s.HighPart ^ local_14.s.LowPart ^
                   local_c.dwHighDateTime ^ local_c.dwLowDateTime ^ DVar1 ^ DVar2 ^ DVar3) & 0xffff;
    if (DAT_0101107c == 0) {
      DAT_0101107c = 0xbb40;
    }
  }
  DAT_01011078 = ~DAT_0101107c;
  return;
}



// ========================================================
// Function: FUN_01008e6b at 01008e6b
// ========================================================

void __fastcall FUN_01008e6b(uint param_1)

{
  HANDLE hProcess;
  int iVar1;
  EXCEPTION_RECORD *pEVar2;
  UINT uExitCode;
  EXCEPTION_RECORD local_334;
  uint local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  _EXCEPTION_POINTERS local_c;
  
  if ((param_1 == DAT_0101107c) && ((param_1 & 0xffff0000) == 0)) {
    return;
  }
  local_2dc = 0x10001;
  pEVar2 = &local_334;
  for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
    pEVar2->ExceptionCode = 0;
    pEVar2 = (EXCEPTION_RECORD *)&pEVar2->ExceptionFlags;
  }
  local_334.ExceptionCode = 0xc0000409;
  local_c.ExceptionRecord = &local_334;
  local_c.ContextRecord = (PCONTEXT)&local_2dc;
  local_2e4 = DAT_0101107c;
  local_2e0 = DAT_01011078;
  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)0x0);
  UnhandledExceptionFilter(&local_c);
  uExitCode = 0x502;
  hProcess = GetCurrentProcess();
  TerminateProcess(hProcess,uExitCode);
  return;
}



// ========================================================
// Function: FUN_01008f83 at 01008f83
// ========================================================

void __cdecl FUN_01008f83(int param_1)

{
  if (DAT_01013054 == 1) {
    __FF_MSGBANNER();
  }
  FUN_01009701(param_1);
  (*(code *)PTR_FUN_01011080)(0xff);
  return;
}



// ========================================================
// Function: entry at 01008fb2
// ========================================================

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

UINT entry(void)

{
  short sVar1;
  int iVar2;
  UINT UVar3;
  _OSVERSIONINFOA local_114;
  _STARTUPINFOA local_74;
  UINT local_30;
  int local_2c;
  byte *local_24;
  uint local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_01001648;
  uStack_c = 0x1008fbe;
  local_114.szCSDVersion[0x7c] = -0x36;
  local_114.szCSDVersion[0x7d] = -0x71;
  local_114.szCSDVersion[0x7e] = '\0';
  local_114.szCSDVersion[0x7f] = '\x01';
  local_1c = (undefined1 *)&local_114;
  local_114.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_114);
  DAT_0101306c = local_114.dwPlatformId;
  DAT_01013078 = local_114.dwMajorVersion;
  _DAT_0101307c = local_114.dwMinorVersion;
  _DAT_01013070 = local_114.dwBuildNumber & 0x7fff;
  if (local_114.dwPlatformId != 2) {
    _DAT_01013070 = _DAT_01013070 | 0x8000;
  }
  _DAT_01013074 = local_114.dwMajorVersion * 0x100 + local_114.dwMinorVersion;
  if ((IMAGE_DOS_HEADER_01000000.e_magic == (char  [2])0x5a4d) &&
     (*(int *)(IMAGE_DOS_HEADER_01000000.e_lfanew + 0x1000000) == 0x4550)) {
    sVar1 = *(short *)((int)IMAGE_DOS_HEADER_01000000.e_res_4_ +
                      (IMAGE_DOS_HEADER_01000000.e_lfanew - 4));
    if (sVar1 == 0x10b) {
      if (0xe < *(uint *)(IMAGE_DOS_HEADER_01000000.e_program +
                         IMAGE_DOS_HEADER_01000000.e_lfanew + 0x34)) {
        iVar2 = *(int *)((int)(IMAGE_NT_HEADERS32_010000d8.OptionalHeader.DataDirectory + -0xd) +
                        IMAGE_DOS_HEADER_01000000.e_lfanew);
        goto LAB_01009075;
      }
    }
    else if ((sVar1 == 0x20b) &&
            (0xe < *(uint *)(&UNK_01000080.field_0x4 + IMAGE_DOS_HEADER_01000000.e_lfanew))) {
      iVar2 = *(int *)((int)(IMAGE_NT_HEADERS32_010000d8.OptionalHeader.DataDirectory + -0xb) +
                      IMAGE_DOS_HEADER_01000000.e_lfanew);
LAB_01009075:
      local_20 = (uint)(iVar2 != 0);
      goto LAB_0100907b;
    }
  }
  local_20 = 0;
LAB_0100907b:
  iVar2 = FUN_0100a112(0);
  if (iVar2 == 0) {
    if (DAT_01013054 == 1) {
      __FF_MSGBANNER();
    }
    FUN_01009701(0x1c);
    FUN_01009560(0xff);
  }
  local_8 = (undefined *)0x0;
  iVar2 = FUN_01009f42();
  if (iVar2 < 0) {
    FUN_01008f83(0x1b);
  }
  DAT_01013650 = GetCommandLineA();
  DAT_0101304c = FUN_01009e15();
  iVar2 = __setargv();
  if (iVar2 < 0) {
    FUN_01008f83(8);
  }
  iVar2 = FUN_01009b12();
  if (iVar2 < 0) {
    FUN_01008f83(9);
  }
  local_2c = FUN_010095ba();
  if (local_2c != 0) {
    FUN_01008f83(local_2c);
  }
  local_74.dwFlags = 0;
  GetStartupInfoA(&local_74);
  local_24 = FUN_01009aa4();
  UVar3 = FUN_010070c0((HINSTANCE)&IMAGE_DOS_HEADER_01000000);
  local_30 = UVar3;
  if (local_20 == 0) {
    FUN_0100969a(UVar3);
  }
  FUN_010096d2();
  return UVar3;
}



// ========================================================
// Function: FUN_01009193 at 01009193
// ========================================================

void FUN_01009193(LPVOID param_1)

{
  FUN_0100a312(param_1);
  return;
}



// ========================================================
// Function: FUN_010091a9 at 010091a9
// ========================================================

void FUN_010091a9(void)

{
  PTR_LAB_010111e0 = __cfltcvt;
  PTR_LAB_010111e4 = FUN_0100a3b6;
  PTR_LAB_010111e8 = __fassign;
  PTR_LAB_010111ec = FUN_0100a354;
  PTR_LAB_010111f0 = FUN_0100a40b;
  PTR_LAB_010111f4 = __cfltcvt;
  return;
}



// ========================================================
// Function: FUN_010091e6 at 010091e6
// ========================================================

void FUN_010091e6(void)

{
  void *extraout_ECX;
  
  FUN_010091a9();
  FUN_0100a773(extraout_ECX);
  return;
}



// ========================================================
// Function: __ftol at 01009200
// ========================================================

/* Library Function - Single Match
    __ftol
   
   Library: Visual Studio */

longlong __ftol(void)

{
  float10 in_ST0;
  
  return (longlong)ROUND(in_ST0);
}



// ========================================================
// Function: FUN_0100922c at 0100922c
// ========================================================

void __cdecl FUN_0100922c(uint *param_1)

{
  FUN_0100a7da(param_1,1);
  return;
}



// ========================================================
// Function: FID_conflict:__time32 at 01009244
// ========================================================

/* Library Function - Multiple Matches With Different Base Names
    __time32
    _time
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

__time32_t __cdecl FID_conflict___time32(__time32_t *_Time)

{
  undefined8 uVar1;
  _FILETIME local_c;
  
  GetSystemTimeAsFileTime(&local_c);
  uVar1 = __aulldiv(local_c.dwLowDateTime + 0x2ac18000,
                    local_c.dwHighDateTime + 0xfe624e21 + (uint)(0xd53e7fff < local_c.dwLowDateTime)
                    ,10000000,0);
  if (_Time != (__time32_t *)0x0) {
    *_Time = (__time32_t)uVar1;
  }
  return (__time32_t)uVar1;
}



// ========================================================
// Function: FUN_01009284 at 01009284
// ========================================================

void __cdecl FUN_01009284(int param_1)

{
  SIZE_T SVar1;
  int *piVar2;
  SIZE_T SVar3;
  
  SVar1 = FUN_0100aa3a(DAT_01013648);
  if (SVar1 < (uint)((int)DAT_01013644 + (4 - (int)DAT_01013648))) {
    SVar3 = 0x800;
    if (SVar1 < 0x800) {
      SVar3 = SVar1;
    }
    piVar2 = FUN_0100a89d(DAT_01013648,(uint *)(SVar3 + SVar1));
    if ((piVar2 == (int *)0x0) &&
       (piVar2 = FUN_0100a89d(DAT_01013648,(uint *)(SVar1 + 0x10)), piVar2 == (int *)0x0)) {
      return;
    }
    DAT_01013644 = piVar2 + ((int)DAT_01013644 - (int)DAT_01013648 >> 2);
    DAT_01013648 = piVar2;
  }
  *DAT_01013644 = param_1;
  DAT_01013644 = DAT_01013644 + 1;
  return;
}



// ========================================================
// Function: FUN_0100930e at 0100930e
// ========================================================

int __cdecl FUN_0100930e(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_01009284(param_1);
  return (iVar1 != 0) - 1;
}



// ========================================================
// Function: ___onexitinit at 0100932a
// ========================================================

/* Library Function - Single Match
    ___onexitinit
   
   Library: Visual Studio 2003 Release */

undefined4 ___onexitinit(void)

{
  DAT_01013648 = (undefined4 *)FUN_0100a80d((uint *)0x80);
  if (DAT_01013648 == (undefined4 *)0x0) {
    return 0x18;
  }
  *DAT_01013648 = 0;
  DAT_01013644 = DAT_01013648;
  return 0;
}



// ========================================================
// Function: FUN_01009357 at 01009357
// ========================================================

void __cdecl FUN_01009357(undefined4 param_1)

{
  DAT_010110a0 = param_1;
  return;
}



// ========================================================
// Function: FUN_0100936b at 0100936b
// ========================================================

ushort FUN_0100936b(void)

{
  int iVar1;
  ushort uVar2;
  
  DAT_010110a0 = DAT_010110a0 * 0x343fd + 0x269ec3;
  iVar1 = DAT_010110a0;
  DAT_010110a0._2_2_ = (ushort)((uint)DAT_010110a0 >> 0x10);
  uVar2 = DAT_010110a0._2_2_ & 0x7fff;
  DAT_010110a0 = iVar1;
  return uVar2;
}



// ========================================================
// Function: FUN_010093a0 at 010093a0
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_010093a0(double param_1,undefined2 param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ushort in_FPUControlWord;
  float10 fVar4;
  double dVar5;
  longlong lVar6;
  undefined8 uVar7;
  
  if ((DAT_01013520 != 0) && ((MXCSR & 0x1f80) == 0x1f80 && (in_FPUControlWord & 0x7f) == 0x7f)) {
    uVar2 = (uint)((ulonglong)param_1 >> 0x20);
    uVar1 = uVar2 >> 0x14;
    lVar6 = CONCAT44(_UNK_01001674,_DAT_01001670 - (uVar2 >> 0x14 & _DAT_010016a0));
    if ((uVar1 & 0x800) == 0) {
      if (uVar1 < 0x3ff) {
        return (float10)0;
      }
      if (uVar1 < 0x433) {
        return (float10)(double)(((ulonglong)param_1 >> lVar6) << lVar6);
      }
    }
    else {
      dVar5 = (double)(((ulonglong)param_1 >> lVar6) << lVar6);
      if (uVar1 < 0xbff) {
        return (float10)(double)((-(ulonglong)(param_1 < _DAT_01001690) | (ulonglong)_DAT_01001690)
                                & _DAT_01001680);
      }
      if (uVar1 < 0xc33) {
        return (float10)(dVar5 - (double)(-(ulonglong)(param_1 < dVar5) & _DAT_01001660));
      }
    }
    if (NAN(param_1)) {
      FUN_0100aa7b(&param_1,&param_1,&param_1,0x3ed);
    }
    return (float10)(double)CONCAT26(param_1._6_2_,param_1._0_6_);
  }
  uVar2 = __ctrlfp();
  uVar1 = (uint)(CONCAT26(param_1._6_2_,param_1._0_6_) >> 0x20);
  if ((param_1._6_2_ & 0x7ff0) == 0x7ff0) {
    iVar3 = __sptype((int)param_1._0_6_,uVar1);
    if (0 < iVar3) {
      if (iVar3 < 3) {
        __ctrlfp();
        return (float10)(double)CONCAT26(param_1._6_2_,param_1._0_6_);
      }
      if (iVar3 == 3) {
        fVar4 = __handle_qnan1(0xb,(double)CONCAT44((int)(CONCAT26(param_1._6_2_,param_1._0_6_) >>
                                                         0x20),(int)param_1._0_6_));
        return fVar4;
      }
    }
    dVar5 = (double)CONCAT26(param_1._6_2_,param_1._0_6_) + _DAT_01001b10;
    uVar7 = CONCAT26(param_1._6_2_,param_1._0_6_);
    uVar1 = 8;
  }
  else {
    fVar4 = __frnd((double)CONCAT44(uVar1,(int)param_1._0_6_));
    dVar5 = (double)fVar4;
    if ((dVar5 == (double)CONCAT26(param_1._6_2_,param_1._0_6_)) || ((uVar2 & 0x20) != 0)) {
      __ctrlfp();
      return (float10)dVar5;
    }
    uVar7 = CONCAT26(param_1._6_2_,param_1._0_6_);
    uVar1 = 0x10;
  }
  fVar4 = (float10)FUN_0100df06(uVar1,0xb,uVar7,dVar5,uVar2);
  return fVar4;
}



// ========================================================
// Function: FUN_0100950c at 0100950c
// ========================================================

void __fastcall FUN_0100950c(undefined4 param_1)

{
  ushort in_FPUControlWord;
  
  if ((DAT_01013520 != 0) && ((MXCSR & 0x1f80) == 0x1f80 && (in_FPUControlWord & 0x7f) == 0x7f)) {
    FUN_0100ae70();
    return;
  }
  __cintrindisp1(param_1,0x1011254);
  return;
}



// ========================================================
// Function: FUN_01009560 at 01009560
// ========================================================

void FUN_01009560(UINT param_1)

{
  HMODULE hModule;
  FARPROC pFVar1;
  
  hModule = GetModuleHandleA("mscoree.dll");
  if (hModule != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(hModule,"CorExitProcess");
    if (pFVar1 != (FARPROC)0x0) {
      (*pFVar1)(param_1);
    }
  }
                    /* WARNING: Subroutine does not return */
  ExitProcess(param_1);
}



// ========================================================
// Function: __initterm at 01009598
// ========================================================

/* Library Function - Single Match
    __initterm
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

void __cdecl __initterm(undefined4 *param_1)

{
  undefined4 *in_EAX;
  
  for (; in_EAX < param_1; in_EAX = in_EAX + 1) {
    if ((code *)*in_EAX != (code *)0x0) {
      (*(code *)*in_EAX)();
    }
  }
  return;
}



// ========================================================
// Function: FUN_010095ba at 010095ba
// ========================================================

int FUN_010095ba(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (PTR_FUN_01011090 != (undefined *)0x0) {
    (*(code *)PTR_FUN_01011090)();
  }
  iVar1 = 0;
  puVar2 = &DAT_01011010;
  do {
    if (iVar1 != 0) {
      return iVar1;
    }
    if ((code *)*puVar2 != (code *)0x0) {
      iVar1 = (*(code *)*puVar2)();
    }
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_01011020);
  if (iVar1 == 0) {
    __initterm((undefined4 *)&DAT_0101100c);
    iVar1 = 0;
  }
  return iVar1;
}



// ========================================================
// Function: FUN_0100960a at 0100960a
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0100960a(UINT param_1,int param_2)

{
  int unaff_EBX;
  bool bVar1;
  
  if (DAT_010130ac != 1) {
    _DAT_010130a8 = 1;
    DAT_010130a4 = (undefined1)unaff_EBX;
    if (param_2 == 0) {
      if (DAT_01013648 != (undefined4 *)0x0) {
        DAT_01013644 = DAT_01013644 + -1;
        bVar1 = DAT_01013644 < DAT_01013648;
        while (!bVar1) {
          if ((code *)*DAT_01013644 != (code *)0x0) {
            (*(code *)*DAT_01013644)();
          }
          DAT_01013644 = DAT_01013644 + -1;
          bVar1 = DAT_01013644 < DAT_01013648;
        }
      }
      __initterm((undefined4 *)&DAT_01011028);
    }
    __initterm((undefined4 *)&DAT_01011030);
  }
  if (unaff_EBX == 0) {
    DAT_010130ac = 1;
    FUN_01009560(param_1);
  }
  return;
}



// ========================================================
// Function: FUN_0100969a at 0100969a
// ========================================================

void __cdecl FUN_0100969a(UINT param_1)

{
  FUN_0100960a(param_1,0);
  return;
}



// ========================================================
// Function: FUN_010096b6 at 010096b6
// ========================================================

void __cdecl FUN_010096b6(UINT param_1)

{
  FUN_0100960a(param_1,1);
  return;
}



// ========================================================
// Function: FUN_010096d2 at 010096d2
// ========================================================

void FUN_010096d2(void)

{
  FUN_0100960a(0,0);
  return;
}



// ========================================================
// Function: FUN_01009701 at 01009701
// ========================================================

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl FUN_01009701(int param_1)

{
  char cVar1;
  int iVar2;
  undefined2 *puVar3;
  uint uVar4;
  DWORD DVar5;
  char *pcVar6;
  char *pcVar7;
  HANDLE hFile;
  char *pcVar8;
  int iVar9;
  CHAR *pCVar10;
  undefined4 *puVar11;
  char *pcVar12;
  undefined2 *puVar13;
  DWORD local_118;
  int local_114;
  CHAR local_110 [260];
  undefined1 local_c;
  uint local_8;
  
  local_8 = DAT_0101107c;
  uVar4 = 0;
  do {
    if (param_1 == (&DAT_010110b0)[uVar4 * 2]) break;
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x12);
  iVar9 = uVar4 * 8;
  local_114 = iVar9;
  if (param_1 == (&DAT_010110b0)[uVar4 * 2]) {
    if ((DAT_01013054 == 1) || ((DAT_01013054 == 0 && (DAT_01011084 == 1)))) {
      hFile = GetStdHandle(0xfffffff4);
      if (hFile != (HANDLE)0x0) {
        pcVar8 = *(char **)(iVar9 + 0x10110b4);
        pcVar6 = pcVar8;
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        WriteFile(hFile,pcVar8,(int)pcVar6 - (int)(pcVar8 + 1),&local_118,(LPOVERLAPPED)0x0);
      }
    }
    else if (param_1 != 0xfc) {
      local_c = 0;
      DVar5 = GetModuleFileNameA((HMODULE)0x0,local_110,0x104);
      if (DVar5 == 0) {
        pcVar8 = "<program name unknown>";
        pCVar10 = local_110;
        for (iVar9 = 5; iVar9 != 0; iVar9 = iVar9 + -1) {
          *(undefined4 *)pCVar10 = *(undefined4 *)pcVar8;
          pcVar8 = pcVar8 + 4;
          pCVar10 = pCVar10 + 4;
        }
        *(undefined2 *)pCVar10 = *(undefined2 *)pcVar8;
        pCVar10[2] = pcVar8[2];
      }
      pcVar8 = local_110;
      pcVar6 = pcVar8;
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      if ((char *)0x3c < pcVar6 + (1 - (int)(local_110 + 1))) {
        pcVar6 = local_110;
        do {
          pcVar8 = pcVar6;
          pcVar6 = pcVar8 + 1;
        } while (*pcVar8 != '\0');
        pcVar8 = pcVar8 + -0x3b;
        _strncpy(pcVar8,"...",3);
      }
      pcVar6 = pcVar8;
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      pcVar7 = *(char **)(local_114 + 0x10110b4);
      pcVar12 = pcVar7 + 1;
      do {
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      iVar2 = -((uint)(pcVar6 + (int)(pcVar7 + (-(int)pcVar12 - (int)(pcVar8 + 1)) + 0x1f)) &
               0xfffffffc);
      *(undefined4 *)(&stack0xfffffed8 + iVar2) = 6;
      pcVar6 = "Runtime Error!\n\nProgram: ";
      puVar11 = (undefined4 *)(&stack0xfffffedc + iVar2);
      for (iVar9 = *(int *)(&stack0xfffffed8 + iVar2); iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar11 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        puVar11 = puVar11 + 1;
      }
      *(undefined2 *)puVar11 = *(undefined2 *)pcVar6;
      pcVar6 = pcVar8;
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      pcVar12 = &stack0xfffffedb + iVar2;
      do {
        pcVar7 = pcVar12 + 1;
        pcVar12 = pcVar12 + 1;
      } while (*pcVar7 != '\0');
      pcVar7 = pcVar8;
      for (uVar4 = (uint)((int)pcVar6 - (int)pcVar8) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar4 = (int)pcVar6 - (int)pcVar8 & 3; iVar9 = local_114, uVar4 != 0; uVar4 = uVar4 - 1)
      {
        *pcVar12 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar12 = pcVar12 + 1;
      }
      puVar3 = (undefined2 *)(&stack0xfffffedb + iVar2);
      do {
        puVar13 = puVar3;
        puVar3 = (undefined2 *)((int)puVar13 + 1);
      } while (*(char *)((int)puVar13 + 1) != '\0');
      *(undefined2 *)((int)puVar13 + 1) = DAT_010019f8;
      *(undefined1 *)((int)puVar13 + 3) = DAT_010019fa;
      pcVar8 = *(char **)(iVar9 + 0x10110b4);
      pcVar6 = pcVar8;
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      pcVar12 = &stack0xfffffedb + iVar2;
      do {
        pcVar7 = pcVar12 + 1;
        pcVar12 = pcVar12 + 1;
      } while (*pcVar7 != '\0');
      pcVar7 = pcVar8;
      for (uVar4 = (uint)((int)pcVar6 - (int)pcVar8) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar12 = pcVar12 + 4;
      }
      *(undefined4 *)(&stack0xfffffed8 + iVar2) = 0x12010;
      *(char **)(&stack0xfffffed4 + iVar2) = "Microsoft Visual C++ Runtime Library";
      *(undefined1 **)(&stack0xfffffed0 + iVar2) = &stack0xfffffedc + iVar2;
      for (uVar4 = (int)pcVar6 - (int)pcVar8 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar12 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar12 = pcVar12 + 1;
      }
      *(undefined4 *)(&stack0xfffffecc + iVar2) = 0x100989f;
      ___crtMessageBoxA(*(LPCSTR *)(&stack0xfffffed0 + iVar2),*(LPCSTR *)(&stack0xfffffed4 + iVar2),
                        *(UINT *)(&stack0xfffffed8 + iVar2));
    }
  }
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: __FF_MSGBANNER at 010098ee
// ========================================================

/* Library Function - Single Match
    __FF_MSGBANNER
   
   Library: Visual Studio 2003 Release */

void __cdecl __FF_MSGBANNER(void)

{
  if ((DAT_01013054 == 1) || ((DAT_01013054 == 0 && (DAT_01011084 == 1)))) {
    FUN_01009701(0xfc);
    if (DAT_010130b0 != (code *)0x0) {
      (*DAT_010130b0)();
    }
    FUN_01009701(0xff);
  }
  return;
}



// ========================================================
// Function: __XcptFilter at 0100992c
// ========================================================

/* Library Function - Single Match
    __XcptFilter
   
   Library: Visual Studio 2003 Release */

int __cdecl __XcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr)

{
  code *pcVar1;
  ulong uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  ulong *puVar6;
  undefined4 *puVar7;
  
  uVar4 = DAT_010130b4;
  puVar6 = &DAT_01011140;
  do {
    if (*puVar6 == _ExceptionNum) break;
    puVar6 = puVar6 + 3;
  } while (puVar6 < &DAT_01011140 + DAT_010111c0 * 3);
  if ((&DAT_01011140 + DAT_010111c0 * 3 <= puVar6) || (*puVar6 != _ExceptionNum)) {
    puVar6 = (ulong *)0x0;
  }
  if ((puVar6 == (ulong *)0x0) || (pcVar1 = (code *)puVar6[2], pcVar1 == (code *)0x0)) {
    iVar5 = UnhandledExceptionFilter(_ExceptionPtr);
  }
  else if (pcVar1 == (code *)0x5) {
    puVar6[2] = 0;
    iVar5 = 1;
  }
  else {
    if (pcVar1 != (code *)0x1) {
      DAT_010130b4 = _ExceptionPtr;
      if (puVar6[1] == 8) {
        if (DAT_010111b8 < DAT_010111bc + DAT_010111b8) {
          puVar7 = (undefined4 *)(DAT_010111b8 * 0xc + 0x1011148);
          iVar5 = (DAT_010111bc + DAT_010111b8) - DAT_010111b8;
          do {
            *puVar7 = 0;
            puVar7 = puVar7 + 3;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
        }
        uVar3 = DAT_010111c4;
        uVar2 = *puVar6;
        if (uVar2 == 0xc000008e) {
          DAT_010111c4 = 0x83;
        }
        else if (uVar2 == 0xc0000090) {
          DAT_010111c4 = 0x81;
        }
        else if (uVar2 == 0xc0000091) {
          DAT_010111c4 = 0x84;
        }
        else if (uVar2 == 0xc0000093) {
          DAT_010111c4 = 0x85;
        }
        else if (uVar2 == 0xc000008d) {
          DAT_010111c4 = 0x82;
        }
        else if (uVar2 == 0xc000008f) {
          DAT_010111c4 = 0x86;
        }
        else if (uVar2 == 0xc0000092) {
          DAT_010111c4 = 0x8a;
        }
        (*pcVar1)(8,DAT_010111c4);
        DAT_010111c4 = uVar3;
      }
      else {
        puVar6[2] = 0;
        (*pcVar1)(puVar6[1]);
      }
    }
    iVar5 = -1;
    DAT_010130b4 = (_EXCEPTION_POINTERS *)uVar4;
  }
  return iVar5;
}



// ========================================================
// Function: FUN_01009aa4 at 01009aa4
// ========================================================

byte * FUN_01009aa4(void)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  
  if (DAT_0101364c == 0) {
    ___initmbctable();
  }
  if (DAT_01013650 == (byte *)0x0) {
    pbVar3 = (byte *)0x1001a33;
  }
  else {
    bVar1 = *DAT_01013650;
    pbVar3 = DAT_01013650;
    if (bVar1 != 0x22) {
      do {
        if (bVar1 < 0x21) goto LAB_01009b03;
        bVar1 = pbVar3[1];
        pbVar3 = pbVar3 + 1;
      } while( true );
    }
    pbVar3 = DAT_01013650 + 1;
    bVar1 = *pbVar3;
    if (bVar1 != 0x22) {
      do {
        if (bVar1 == 0) break;
        iVar2 = FUN_0100b7ec(bVar1);
        if (iVar2 != 0) {
          pbVar3 = pbVar3 + 1;
        }
        pbVar3 = pbVar3 + 1;
        bVar1 = *pbVar3;
      } while (bVar1 != 0x22);
      if (*pbVar3 != 0x22) goto LAB_01009b03;
    }
    do {
      pbVar3 = pbVar3 + 1;
LAB_01009b03:
    } while ((*pbVar3 != 0) && (*pbVar3 < 0x21));
  }
  return pbVar3;
}



// ========================================================
// Function: FUN_01009b12 at 01009b12
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_01009b12(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  
  iVar8 = 0;
  if (DAT_0101364c == 0) {
    ___initmbctable();
  }
  pcVar6 = DAT_0101304c;
  if (DAT_0101304c != (char *)0x0) {
    while (*pcVar6 != '\0') {
      if (*pcVar6 != '=') {
        iVar8 = iVar8 + 1;
      }
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
    }
    puVar2 = (undefined4 *)FUN_0100a80d((uint *)(iVar8 * 4 + 4));
    pcVar6 = DAT_0101304c;
    DAT_0101308c = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      uVar3 = 0xffffffff;
    }
    else {
      for (; *pcVar6 != '\0'; pcVar6 = pcVar6 + (int)(pcVar4 + (1 - (int)(pcVar6 + 1)))) {
        pcVar4 = pcVar6;
        do {
          cVar1 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        if (*pcVar6 != '=') {
          pcVar5 = (char *)FUN_0100a80d((uint *)(pcVar4 + (1 - (int)(pcVar6 + 1))));
          *puVar2 = pcVar5;
          pcVar7 = pcVar6;
          if (pcVar5 == (char *)0x0) {
            FUN_0100a312(DAT_0101308c);
            DAT_0101308c = (undefined4 *)0x0;
            return 0xffffffff;
          }
          do {
            cVar1 = *pcVar7;
            *pcVar5 = cVar1;
            pcVar5 = pcVar5 + 1;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          puVar2 = puVar2 + 1;
        }
      }
      FUN_0100a312(DAT_0101304c);
      DAT_0101304c = (char *)0x0;
      *puVar2 = 0;
      _DAT_01013640 = 1;
      uVar3 = 0;
    }
    return uVar3;
  }
  return 0xffffffff;
}



// ========================================================
// Function: parse_cmdline at 01009bf9
// ========================================================

/* Library Function - Single Match
    _parse_cmdline
   
   Library: Visual Studio 2003 Release */

void __cdecl parse_cmdline(undefined4 *param_1,int *param_2)

{
  bool bVar1;
  bool bVar2;
  byte *in_EAX;
  byte *pbVar3;
  byte *pbVar4;
  byte bVar5;
  byte *in_ECX;
  uint uVar6;
  int *unaff_ESI;
  
  bVar1 = false;
  *unaff_ESI = 0;
  *param_2 = 1;
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = in_ECX;
    param_1 = param_1 + 1;
  }
  do {
    if (*in_EAX == 0x22) {
      bVar1 = !bVar1;
      pbVar3 = in_EAX + 1;
      bVar5 = 0x22;
    }
    else {
      *unaff_ESI = *unaff_ESI + 1;
      if (in_ECX != (byte *)0x0) {
        *in_ECX = *in_EAX;
        in_ECX = in_ECX + 1;
      }
      bVar5 = *in_EAX;
      pbVar3 = in_EAX + 1;
      if ((*(byte *)((int)&DAT_01013300 + bVar5 + 1) & 4) != 0) {
        *unaff_ESI = *unaff_ESI + 1;
        if (in_ECX != (byte *)0x0) {
          *in_ECX = *pbVar3;
          in_ECX = in_ECX + 1;
        }
        pbVar3 = in_EAX + 2;
      }
      if (bVar5 == 0) {
        pbVar3 = pbVar3 + -1;
        goto LAB_01009c74;
      }
    }
    in_EAX = pbVar3;
  } while ((bVar1) || ((bVar5 != 0x20 && (bVar5 != 9))));
  if (in_ECX != (byte *)0x0) {
    in_ECX[-1] = 0;
  }
LAB_01009c74:
  bVar1 = false;
  while (*pbVar3 != 0) {
    for (; (*pbVar3 == 0x20 || (*pbVar3 == 9)); pbVar3 = pbVar3 + 1) {
    }
    if (*pbVar3 == 0) break;
    if (param_1 != (undefined4 *)0x0) {
      *param_1 = in_ECX;
      param_1 = param_1 + 1;
    }
    *param_2 = *param_2 + 1;
    while( true ) {
      bVar2 = true;
      uVar6 = 0;
      for (; *pbVar3 == 0x5c; pbVar3 = pbVar3 + 1) {
        uVar6 = uVar6 + 1;
      }
      if (*pbVar3 == 0x22) {
        pbVar4 = pbVar3;
        if ((uVar6 & 1) == 0) {
          if ((!bVar1) || (pbVar4 = pbVar3 + 1, *pbVar4 != 0x22)) {
            bVar2 = false;
            pbVar4 = pbVar3;
          }
          bVar1 = !bVar1;
        }
        uVar6 = uVar6 >> 1;
        pbVar3 = pbVar4;
      }
      for (; uVar6 != 0; uVar6 = uVar6 - 1) {
        if (in_ECX != (byte *)0x0) {
          *in_ECX = 0x5c;
          in_ECX = in_ECX + 1;
        }
        *unaff_ESI = *unaff_ESI + 1;
      }
      bVar5 = *pbVar3;
      if ((bVar5 == 0) || ((!bVar1 && ((bVar5 == 0x20 || (bVar5 == 9)))))) break;
      if (bVar2) {
        if (in_ECX == (byte *)0x0) {
          if ((*(byte *)((int)&DAT_01013300 + bVar5 + 1) & 4) != 0) {
            pbVar3 = pbVar3 + 1;
            *unaff_ESI = *unaff_ESI + 1;
          }
        }
        else {
          if ((*(byte *)((int)&DAT_01013300 + bVar5 + 1) & 4) != 0) {
            *in_ECX = bVar5;
            in_ECX = in_ECX + 1;
            pbVar3 = pbVar3 + 1;
            *unaff_ESI = *unaff_ESI + 1;
          }
          *in_ECX = *pbVar3;
          in_ECX = in_ECX + 1;
        }
        *unaff_ESI = *unaff_ESI + 1;
      }
      pbVar3 = pbVar3 + 1;
    }
    if (in_ECX != (byte *)0x0) {
      *in_ECX = 0;
      in_ECX = in_ECX + 1;
    }
    *unaff_ESI = *unaff_ESI + 1;
  }
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = 0;
  }
  *param_2 = *param_2 + 1;
  return;
}



// ========================================================
// Function: __setargv at 01009d6c
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __setargv
   
   Library: Visual Studio 2003 Release */

int __cdecl __setargv(void)

{
  undefined4 *puVar1;
  int iVar2;
  int in_ECX;
  int local_8;
  
  local_8 = in_ECX;
  if (DAT_0101364c == 0) {
    ___initmbctable();
  }
  DAT_010131bc = 0;
  GetModuleFileNameA((HMODULE)0x0,&DAT_010130b8,0x104);
  _DAT_0101309c = &DAT_010130b8;
  parse_cmdline((undefined4 *)0x0,&local_8);
  puVar1 = (undefined4 *)FUN_0100a80d((uint *)(in_ECX + local_8 * 4));
  if (puVar1 == (undefined4 *)0x0) {
    iVar2 = -1;
  }
  else {
    parse_cmdline(puVar1,&local_8);
    _DAT_01013080 = local_8 + -1;
    iVar2 = 0;
    _DAT_01013084 = puVar1;
  }
  return iVar2;
}



// ========================================================
// Function: FUN_01009e15 at 01009e15
// ========================================================

LPSTR FUN_01009e15(void)

{
  char cVar1;
  WCHAR WVar2;
  DWORD DVar3;
  WCHAR *pWVar4;
  WCHAR *pWVar5;
  int iVar6;
  uint *puVar7;
  LPSTR pCVar8;
  LPCH pCVar9;
  char *pcVar10;
  uint uVar12;
  CHAR *pCVar13;
  LPWCH lpWideCharStr;
  LPSTR pCVar14;
  LPSTR local_8;
  char *pcVar11;
  
  local_8 = (LPSTR)0x0;
  lpWideCharStr = (LPWCH)0x0;
  if (DAT_010131c0 == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr != (LPWCH)0x0) {
      DAT_010131c0 = 1;
      goto LAB_01009e66;
    }
    DVar3 = GetLastError();
    if (DVar3 == 0x78) {
      DAT_010131c0 = 2;
    }
  }
  if (DAT_010131c0 != 1) {
    if ((DAT_010131c0 != 2) && (DAT_010131c0 != 0)) {
      return (LPSTR)0x0;
    }
    pCVar9 = GetEnvironmentStrings();
    if (pCVar9 == (LPCH)0x0) {
      return (LPSTR)0x0;
    }
    cVar1 = *pCVar9;
    pcVar10 = pCVar9;
    while (cVar1 != '\0') {
      do {
        pcVar11 = pcVar10;
        pcVar10 = pcVar11 + 1;
      } while (*pcVar10 != '\0');
      pcVar10 = pcVar11 + 2;
      cVar1 = *pcVar10;
    }
    puVar7 = (uint *)(pcVar10 + (1 - (int)pCVar9));
    pCVar8 = (LPSTR)FUN_0100a80d(puVar7);
    if (pCVar8 != (LPSTR)0x0) {
      pCVar13 = pCVar9;
      pCVar14 = pCVar8;
      for (uVar12 = (uint)puVar7 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pCVar14 = *(undefined4 *)pCVar13;
        pCVar13 = pCVar13 + 4;
        pCVar14 = pCVar14 + 4;
      }
      for (uVar12 = (uint)puVar7 & 3; local_8 = pCVar8, uVar12 != 0; uVar12 = uVar12 - 1) {
        *pCVar14 = *pCVar13;
        pCVar13 = pCVar13 + 1;
        pCVar14 = pCVar14 + 1;
      }
    }
    FreeEnvironmentStringsA(pCVar9);
    return local_8;
  }
LAB_01009e66:
  if ((lpWideCharStr == (LPWCH)0x0) &&
     (lpWideCharStr = GetEnvironmentStringsW(), lpWideCharStr == (LPWCH)0x0)) {
    return (LPSTR)0x0;
  }
  WVar2 = *lpWideCharStr;
  pWVar5 = lpWideCharStr;
  while (WVar2 != L'\0') {
    do {
      pWVar4 = pWVar5;
      pWVar5 = pWVar4 + 1;
    } while (*pWVar5 != L'\0');
    pWVar5 = pWVar4 + 2;
    WVar2 = *pWVar5;
  }
  iVar6 = ((int)pWVar5 - (int)lpWideCharStr >> 1) + 1;
  puVar7 = (uint *)WideCharToMultiByte(0,0,lpWideCharStr,iVar6,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0)
  ;
  if (((puVar7 != (uint *)0x0) && (pCVar8 = (LPSTR)FUN_0100a80d(puVar7), pCVar8 != (LPSTR)0x0)) &&
     (iVar6 = WideCharToMultiByte(0,0,lpWideCharStr,iVar6,pCVar8,(int)puVar7,(LPCSTR)0x0,(LPBOOL)0x0
                                 ), local_8 = pCVar8, iVar6 == 0)) {
    FUN_0100a312(pCVar8);
    local_8 = (LPSTR)0x0;
  }
  FreeEnvironmentStringsW(lpWideCharStr);
  return local_8;
}



// ========================================================
// Function: FUN_01009f42 at 01009f42
// ========================================================

undefined4 FUN_01009f42(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  DWORD DVar5;
  HANDLE hFile;
  UINT *pUVar6;
  int iVar7;
  uint uVar8;
  UINT UVar9;
  UINT UVar10;
  _STARTUPINFOA local_4c;
  byte *local_8;
  
  puVar3 = (undefined4 *)FUN_0100a80d((uint *)0x100);
  if (puVar3 == (undefined4 *)0x0) {
    return 0xffffffff;
  }
  DAT_01013530 = 0x20;
  DAT_01013540 = puVar3;
  for (; puVar3 < DAT_01013540 + 0x40; puVar3 = puVar3 + 2) {
    *puVar3 = 0xffffffff;
    *(undefined1 *)(puVar3 + 1) = 0;
    *(undefined1 *)((int)puVar3 + 5) = 10;
  }
  GetStartupInfoA(&local_4c);
  if ((local_4c.cbReserved2 != 0) && ((UINT *)local_4c.lpReserved2 != (UINT *)0x0)) {
    UVar9 = *(UINT *)local_4c.lpReserved2;
    pUVar6 = (UINT *)((int)local_4c.lpReserved2 + 4);
    local_8 = (byte *)((int)pUVar6 + UVar9);
    if (0x7ff < (int)UVar9) {
      UVar9 = 0x800;
    }
    UVar10 = UVar9;
    if ((int)DAT_01013530 < (int)UVar9) {
      puVar3 = &DAT_01013544;
      do {
        puVar4 = (undefined4 *)FUN_0100a80d((uint *)0x100);
        UVar10 = DAT_01013530;
        if (puVar4 == (undefined4 *)0x0) break;
        DAT_01013530 = DAT_01013530 + 0x20;
        *puVar3 = puVar4;
        puVar2 = puVar4;
        for (; puVar4 < puVar2 + 0x40; puVar4 = puVar4 + 2) {
          *puVar4 = 0xffffffff;
          *(undefined1 *)(puVar4 + 1) = 0;
          *(undefined1 *)((int)puVar4 + 5) = 10;
          puVar2 = (undefined4 *)*puVar3;
        }
        puVar3 = puVar3 + 1;
        UVar10 = UVar9;
      } while ((int)DAT_01013530 < (int)UVar9);
    }
    uVar8 = 0;
    if (0 < (int)UVar10) {
      do {
        if (((*(HANDLE *)local_8 != (HANDLE)0xffffffff) && ((*pUVar6 & 1) != 0)) &&
           (((*pUVar6 & 8) != 0 || (DVar5 = GetFileType(*(HANDLE *)local_8), DVar5 != 0)))) {
          puVar3 = (undefined4 *)((int)(&DAT_01013540)[(int)uVar8 >> 5] + (uVar8 & 0x1f) * 8);
          *puVar3 = *(undefined4 *)local_8;
          *(byte *)(puVar3 + 1) = (byte)*pUVar6;
        }
        local_8 = local_8 + 4;
        uVar8 = uVar8 + 1;
        pUVar6 = (UINT *)((int)pUVar6 + 1);
      } while ((int)uVar8 < (int)UVar10);
    }
  }
  iVar7 = 0;
  do {
    piVar1 = DAT_01013540 + iVar7 * 2;
    if (*piVar1 == -1) {
      *(undefined1 *)(piVar1 + 1) = 0x81;
      if (iVar7 == 0) {
        DVar5 = 0xfffffff6;
      }
      else {
        DVar5 = 0xfffffff5 - (iVar7 != 1);
      }
      hFile = GetStdHandle(DVar5);
      if ((hFile != (HANDLE)0xffffffff) && (DVar5 = GetFileType(hFile), DVar5 != 0)) {
        *piVar1 = (int)hFile;
        if ((DVar5 & 0xff) != 2) {
          if ((DVar5 & 0xff) == 3) {
            *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 8;
          }
          goto LAB_0100a0d5;
        }
      }
      *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 0x40;
    }
    else {
      *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 0x80;
    }
LAB_0100a0d5:
    iVar7 = iVar7 + 1;
    if (2 < iVar7) {
      SetHandleCount(DAT_01013530);
      return 0;
    }
  } while( true );
}



// ========================================================
// Function: FUN_0100a0f3 at 0100a0f3
// ========================================================

undefined4 FUN_0100a0f3(void)

{
  if ((DAT_0101306c == 2) && (4 < DAT_01013078)) {
    return 1;
  }
  return 3;
}



// ========================================================
// Function: FUN_0100a112 at 0100a112
// ========================================================

undefined4 __cdecl FUN_0100a112(int param_1)

{
  int iVar1;
  
  DAT_01013528 = HeapCreate((uint)(param_1 == 0),0x1000,0);
  if (DAT_01013528 == (HANDLE)0x0) {
    return 0;
  }
  DAT_0101352c = FUN_0100a0f3();
  if ((DAT_0101352c == 3) && (iVar1 = FUN_0100bc17(0x3f8), iVar1 == 0)) {
    HeapDestroy(DAT_01013528);
    return 0;
  }
  return 1;
}



// ========================================================
// Function: __SEH_prolog at 0100a170
// ========================================================

/* WARNING: This is an inlined function */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Variable defined which should be unmapped: param_2 */
/* Library Function - Single Match
    __SEH_prolog
   
   Library: Visual Studio */

void __cdecl __SEH_prolog(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 unaff_retaddr;
  undefined4 auStack_18 [4];
  undefined1 local_8 [8];
  
  iVar1 = -param_2;
  *(undefined4 *)((int)auStack_18 + iVar1 + 0xc) = unaff_EBX;
  *(undefined4 *)((int)auStack_18 + iVar1 + 8) = unaff_ESI;
  *(undefined4 *)((int)auStack_18 + iVar1 + 4) = unaff_EDI;
  *(undefined4 *)((int)auStack_18 + iVar1) = unaff_retaddr;
  ExceptionList = local_8;
  return;
}



// ========================================================
// Function: __SEH_epilog at 0100a1ab
// ========================================================

/* WARNING: This is an inlined function */
/* Library Function - Single Match
    __SEH_epilog
   
   Library: Visual Studio */

void __SEH_epilog(void)

{
  undefined4 *unaff_EBP;
  undefined4 unaff_retaddr;
  
  ExceptionList = (void *)unaff_EBP[-4];
  *unaff_EBP = unaff_retaddr;
  return;
}



// ========================================================
// Function: FUN_0100a2aa at 0100a2aa
// ========================================================

void FUN_0100a2aa(int param_1)

{
  FUN_0100c7cb(*(int *)(param_1 + 0x18),*(uint *)(param_1 + 0x1c));
  return;
}



// ========================================================
// Function: __chkstk at 0100a2d0
// ========================================================

/* WARNING: This is an inlined function */
/* WARNING: Unable to track spacebase fully for stack */
/* Library Function - Single Match
    __chkstk
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void __chkstk(void)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  if (in_EAX < 0x1000) {
    *(undefined4 *)(&stack0x00000000 + -in_EAX) = unaff_retaddr;
    return;
  }
  puVar1 = &stack0x00000004;
  do {
    puVar1 = puVar1 + -0x1000;
    in_EAX = in_EAX - 0x1000;
  } while (0xfff < in_EAX);
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}



// ========================================================
// Function: FUN_0100a312 at 0100a312
// ========================================================

void __cdecl FUN_0100a312(LPVOID param_1)

{
  uint *puVar1;
  
  if (param_1 != (LPVOID)0x0) {
    if ((DAT_0101352c == 3) && (puVar1 = (uint *)FUN_0100bc6a((int)param_1), puVar1 != (uint *)0x0))
    {
      ___sbh_free_block(puVar1,(int)param_1);
      return;
    }
    HeapFree(DAT_01013528,0,param_1);
  }
  return;
}



// ========================================================
// Function: FUN_0100a354 at 0100a354
// ========================================================

void __cdecl FUN_0100a354(char *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = _tolower((int)*param_1);
  if (iVar3 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (DAT_01011388 < 2) {
        uVar4 = (byte)PTR_DAT_01011394[*param_1 * 2] & 4;
      }
      else {
        uVar4 = __isctype((int)*param_1,4);
      }
    } while (uVar4 != 0);
  }
  cVar2 = *param_1;
  *param_1 = DAT_0101138c;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}



// ========================================================
// Function: FUN_0100a3b6 at 0100a3b6
// ========================================================

void __cdecl FUN_0100a3b6(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  for (; (*param_1 != '\0' && (*param_1 != DAT_0101138c)); param_1 = param_1 + 1) {
  }
  if (*param_1 != '\0') {
    do {
      param_1 = param_1 + 1;
      cVar1 = *param_1;
      pcVar2 = param_1;
      if ((cVar1 == '\0') || (cVar1 == 'e')) break;
    } while (cVar1 != 'E');
    do {
      pcVar3 = pcVar2;
      pcVar2 = pcVar3 + -1;
    } while (*pcVar2 == '0');
    if (*pcVar2 == DAT_0101138c) {
      pcVar2 = pcVar3 + -2;
    }
    do {
      cVar1 = *param_1;
      pcVar2 = pcVar2 + 1;
      param_1 = param_1 + 1;
      *pcVar2 = cVar1;
    } while (cVar1 != '\0');
  }
  return;
}



// ========================================================
// Function: FUN_0100a40b at 0100a40b
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0100a40b(double *param_1)

{
  if (_DAT_01001a38 <= *param_1) {
    return 1;
  }
  return 0;
}



// ========================================================
// Function: __fassign at 0100a430
// ========================================================

/* Library Function - Single Match
    __fassign
   
   Library: Visual Studio 2003 Release */

void __cdecl __fassign(int flag,char *argument,char *number)

{
  uint local_c;
  undefined4 local_8;
  
  if (flag != 0) {
    FUN_0100cf8e(&local_c,(byte *)number);
    *(uint *)argument = local_c;
    *(undefined4 *)(argument + 4) = local_8;
    return;
  }
  FUN_0100cfd6((uint *)&flag,(byte *)number);
  *(int *)argument = flag;
  return;
}



// ========================================================
// Function: __shift at 0100a475
// ========================================================

/* Library Function - Single Match
    __shift
   
   Library: Visual Studio 2003 Release */

void __shift(void)

{
  char *in_EAX;
  size_t sVar1;
  int unaff_EDI;
  
  if (unaff_EDI != 0) {
    sVar1 = _strlen(in_EAX);
    FUN_0100d020((undefined4 *)(in_EAX + unaff_EDI),(undefined4 *)in_EAX,sVar1 + 1);
  }
  return;
}



// ========================================================
// Function: __cftoe at 0100a497
// ========================================================

/* Library Function - Single Match
    __cftoe
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl __cftoe(double *_Value,char *_Buf,size_t _SizeInBytes,int _Dec,int _Caps)

{
  int *piVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  piVar1 = DAT_010131c4;
  if (DAT_010131c8 == '\0') {
    piVar1 = (int *)__fltout();
    FUN_0100d4d5(_Buf + (uint)(0 < (int)_SizeInBytes) + (uint)(*piVar1 == 0x2d),_SizeInBytes + 1,
                 (int)piVar1);
  }
  else {
    __shift();
  }
  pcVar2 = _Buf;
  if (*piVar1 == 0x2d) {
    *_Buf = '-';
    pcVar2 = _Buf + 1;
  }
  pcVar3 = pcVar2;
  if (0 < (int)_SizeInBytes) {
    pcVar3 = pcVar2 + 1;
    *pcVar2 = *pcVar3;
    *pcVar3 = DAT_0101138c;
  }
  pcVar2 = FID_conflict___mbscpy(pcVar3 + _SizeInBytes + (DAT_010131c8 == '\0'),"e+000");
  if (_Dec != 0) {
    *pcVar2 = 'E';
  }
  if (*(char *)piVar1[3] != '0') {
    iVar4 = piVar1[1] + -1;
    if (iVar4 < 0) {
      iVar4 = -iVar4;
      pcVar2[1] = '-';
    }
    if (99 < iVar4) {
      iVar5 = iVar4 / 100;
      iVar4 = iVar4 % 100;
      pcVar2[2] = pcVar2[2] + (char)iVar5;
    }
    if (9 < iVar4) {
      iVar5 = iVar4 / 10;
      iVar4 = iVar4 % 10;
      pcVar2[3] = pcVar2[3] + (char)iVar5;
    }
    pcVar2[4] = pcVar2[4] + (char)iVar4;
  }
  return (errno_t)_Buf;
}



// ========================================================
// Function: FUN_0100a58f at 0100a58f
// ========================================================

undefined1 * __cdecl FUN_0100a58f(undefined4 param_1,undefined1 *param_2,size_t param_3)

{
  int *piVar1;
  int iVar2;
  undefined1 *puVar3;
  size_t sVar4;
  
  piVar1 = DAT_010131c4;
  if (DAT_010131c8 == '\0') {
    piVar1 = (int *)__fltout();
    FUN_0100d4d5(param_2 + (*piVar1 == 0x2d),piVar1[1] + param_3,(int)piVar1);
  }
  else if (DAT_010131cc == param_3) {
    iVar2 = (*DAT_010131c4 == 0x2d) + DAT_010131cc;
    param_2[iVar2] = 0x30;
    (param_2 + iVar2)[1] = 0;
  }
  puVar3 = param_2;
  if (*piVar1 == 0x2d) {
    *param_2 = 0x2d;
    puVar3 = param_2 + 1;
  }
  if (piVar1[1] < 1) {
    __shift();
    *puVar3 = 0x30;
    puVar3 = puVar3 + 1;
  }
  else {
    puVar3 = puVar3 + piVar1[1];
  }
  if (0 < (int)param_3) {
    __shift();
    *puVar3 = DAT_0101138c;
    if (piVar1[1] < 0) {
      sVar4 = -piVar1[1];
      if ((DAT_010131c8 != '\0') || ((int)sVar4 <= (int)param_3)) {
        param_3 = sVar4;
      }
      __shift();
      _memset(puVar3 + 1,0x30,param_3);
    }
  }
  return param_2;
}



// ========================================================
// Function: __cftog at 0100a66a
// ========================================================

/* Library Function - Single Match
    __cftog
   
   Library: Visual Studio 2003 Release */

void __cdecl __cftog(double *param_1,char *param_2,size_t param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int unaff_EDI;
  char *pcVar4;
  
  DAT_010131c4 = (int *)__fltout();
  DAT_010131cc = DAT_010131c4[1] + -1;
  iVar1 = *DAT_010131c4;
  FUN_0100d4d5(param_2 + (iVar1 == 0x2d),param_3,(int)DAT_010131c4);
  iVar3 = DAT_010131c4[1] + -1;
  DAT_010131d0 = DAT_010131cc < iVar3;
  DAT_010131cc = iVar3;
  if ((iVar3 < -4) || ((int)param_3 <= iVar3)) {
    DAT_010131c8 = 1;
    __cftoe(param_1,param_2,param_3,param_4,unaff_EDI);
  }
  else {
    pcVar2 = param_2 + (iVar1 == 0x2d);
    if ((bool)DAT_010131d0) {
      do {
        pcVar4 = pcVar2;
        pcVar2 = pcVar4 + 1;
      } while (*pcVar4 != '\0');
      pcVar4[-1] = '\0';
    }
    DAT_010131c8 = 1;
    FUN_0100a58f(param_1,param_2,param_3);
  }
  DAT_010131c8 = 0;
  return;
}



// ========================================================
// Function: __cfltcvt at 0100a71b
// ========================================================

/* Library Function - Single Match
    __cfltcvt
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl
__cfltcvt(double *arg,char *buffer,size_t sizeInBytes,int format,int precision,int caps)

{
  undefined1 *puVar1;
  errno_t eVar2;
  int unaff_EBP;
  
  if ((sizeInBytes == 0x65) || (sizeInBytes == 0x45)) {
    eVar2 = __cftoe(arg,buffer,format,precision,unaff_EBP);
  }
  else {
    if (sizeInBytes == 0x66) {
      puVar1 = FUN_0100a58f(arg,buffer,format);
      return (errno_t)puVar1;
    }
    eVar2 = __cftog(arg,buffer,format,precision);
  }
  return eVar2;
}



// ========================================================
// Function: FUN_0100a773 at 0100a773
// ========================================================

void __fastcall FUN_0100a773(void *param_1)

{
  FUN_0100d879(param_1,0x10000,0x30000);
  return;
}



// ========================================================
// Function: FUN_0100a78a at 0100a78a
// ========================================================

void __cdecl FUN_0100a78a(uint *param_1)

{
  int *piVar1;
  
  if (((DAT_0101352c == 3) && (param_1 <= DAT_010132cc)) &&
     (piVar1 = ___sbh_alloc_block(param_1), piVar1 != (int *)0x0)) {
    return;
  }
  if (param_1 == (uint *)0x0) {
    param_1 = (uint *)0x1;
  }
  if (DAT_0101352c != 1) {
    param_1 = (uint *)((int)param_1 + 0xfU & 0xfffffff0);
  }
  HeapAlloc(DAT_01013528,0,(SIZE_T)param_1);
  return;
}



// ========================================================
// Function: FUN_0100a7da at 0100a7da
// ========================================================

int __cdecl FUN_0100a7da(uint *param_1,int param_2)

{
  int iVar1;
  
  if (param_1 < (uint *)0xffffffe1) {
    do {
      iVar1 = FUN_0100a78a(param_1);
      if (iVar1 != 0) {
        return iVar1;
      }
      if (param_2 == 0) {
        return 0;
      }
      iVar1 = FUN_0100d898(param_1);
    } while (iVar1 != 0);
  }
  return 0;
}



// ========================================================
// Function: FUN_0100a80d at 0100a80d
// ========================================================

void __cdecl FUN_0100a80d(uint *param_1)

{
  FUN_0100a7da(param_1,DAT_01013284);
  return;
}



// ========================================================
// Function: __aulldiv at 0100a830
// ========================================================

/* Library Function - Single Match
    __aulldiv
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

undefined8 __aulldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar6;
  
  uVar9 = param_1;
  uVar6 = param_4;
  uVar7 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar6 >> 1;
      uVar3 = (uint)(CONCAT14((uVar6 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar7 >> 1;
      uVar9 = (uint)(CONCAT14((uVar7 & 1) != 0,uVar9) >> 1);
      uVar6 = uVar5;
      uVar7 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar9) / (ulonglong)uVar3;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar9 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar9)) ||
       ((param_2 <= uVar9 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT44(uVar3,iVar4);
}



// ========================================================
// Function: FUN_0100a89d at 0100a89d
// ========================================================

int * __cdecl FUN_0100a89d(int *param_1,uint *param_2)

{
  int *piVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint *dwBytes;
  uint *puVar5;
  uint *puVar6;
  uint *local_8;
  
  if (param_1 == (int *)0x0) {
    piVar1 = (int *)FUN_0100a80d(param_2);
  }
  else {
    if (param_2 == (uint *)0x0) {
      FUN_0100a312(param_1);
    }
    else {
      dwBytes = param_2;
      if (DAT_0101352c == 3) {
        do {
          param_2 = (uint *)0x0;
          if (dwBytes < (uint *)0xffffffe1) {
            local_8 = (uint *)FUN_0100bc6a((int)param_1);
            if (local_8 == (uint *)0x0) {
LAB_0100a9b8:
              if (dwBytes == (uint *)0x0) {
                dwBytes = (uint *)0x1;
              }
              dwBytes = (uint *)((int)dwBytes + 0xfU & 0xfffffff0);
              param_2 = HeapReAlloc(DAT_01013528,0,param_1,(SIZE_T)dwBytes);
            }
            else {
              if (DAT_010132cc < dwBytes) {
LAB_0100a964:
                if (dwBytes == (uint *)0x0) {
                  dwBytes = (uint *)0x1;
                }
                dwBytes = (uint *)((int)dwBytes + 0xfU & 0xfffffff0);
                param_2 = HeapAlloc(DAT_01013528,0,(SIZE_T)dwBytes);
                if (param_2 != (uint *)0x0) {
                  puVar3 = (uint *)(param_1[-1] - 1U);
                  if (dwBytes <= (uint *)(param_1[-1] - 1U)) {
                    puVar3 = dwBytes;
                  }
                  puVar5 = (uint *)param_1;
                  puVar6 = param_2;
                  for (uVar4 = (uint)puVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                    *puVar6 = *puVar5;
                    puVar5 = puVar5 + 1;
                    puVar6 = puVar6 + 1;
                  }
                  for (uVar4 = (uint)puVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                    *(char *)puVar6 = (char)*puVar5;
                    puVar5 = (uint *)((int)puVar5 + 1);
                    puVar6 = (uint *)((int)puVar6 + 1);
                  }
                  ___sbh_free_block(local_8,(int)param_1);
                }
              }
              else {
                iVar2 = ___sbh_resize_block(local_8,(int)param_1,(int)dwBytes);
                param_2 = (uint *)param_1;
                if (iVar2 == 0) {
                  param_2 = (uint *)___sbh_alloc_block(dwBytes);
                  if (param_2 == (uint *)0x0) goto LAB_0100a964;
                  puVar3 = (uint *)(param_1[-1] - 1U);
                  if (dwBytes <= (uint *)(param_1[-1] - 1U)) {
                    puVar3 = dwBytes;
                  }
                  puVar5 = (uint *)param_1;
                  puVar6 = param_2;
                  for (uVar4 = (uint)puVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                    *puVar6 = *puVar5;
                    puVar5 = puVar5 + 1;
                    puVar6 = puVar6 + 1;
                  }
                  for (uVar4 = (uint)puVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                    *(char *)puVar6 = (char)*puVar5;
                    puVar5 = (uint *)((int)puVar5 + 1);
                    puVar6 = (uint *)((int)puVar6 + 1);
                  }
                  local_8 = (uint *)FUN_0100bc6a((int)param_1);
                  ___sbh_free_block(local_8,(int)param_1);
                }
                if (param_2 == (uint *)0x0) goto LAB_0100a964;
              }
              if (local_8 == (uint *)0x0) goto LAB_0100a9b8;
            }
            if (param_2 != (uint *)0x0) {
              return (int *)param_2;
            }
          }
          if (DAT_01013284 == 0) {
            return (int *)param_2;
          }
          iVar2 = FUN_0100d898(dwBytes);
        } while (iVar2 != 0);
      }
      else {
        do {
          if (param_2 < (uint *)0xffffffe1) {
            if (param_2 == (uint *)0x0) {
              param_2 = (uint *)0x1;
            }
            piVar1 = HeapReAlloc(DAT_01013528,0,param_1,(SIZE_T)param_2);
            if (piVar1 != (int *)0x0) {
              return piVar1;
            }
          }
          if (DAT_01013284 == 0) {
            return (int *)0x0;
          }
          iVar2 = FUN_0100d898(param_2);
        } while (iVar2 != 0);
      }
    }
    piVar1 = (int *)0x0;
  }
  return piVar1;
}



// ========================================================
// Function: FUN_0100aa3a at 0100aa3a
// ========================================================

SIZE_T __cdecl FUN_0100aa3a(LPCVOID param_1)

{
  uint uVar1;
  SIZE_T SVar2;
  
  if ((DAT_0101352c == 3) && (uVar1 = FUN_0100bc6a((int)param_1), uVar1 != 0)) {
    SVar2 = *(int *)((int)param_1 + -4) - 9;
  }
  else {
    SVar2 = HeapSize(DAT_01013528,0,param_1);
  }
  return SVar2;
}



// ========================================================
// Function: FUN_0100aa7b at 0100aa7b
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_0100aa7b(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,int param_4)

{
  undefined8 uVar1;
  int iVar2;
  undefined4 local_28;
  char *local_24;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_0101107c;
  if (0xa1 < param_4) {
    if (param_4 < 0x3eb) {
      if (param_4 != 0x3ea) {
        if (param_4 == 0xa2) {
          local_28 = 4;
          goto LAB_0100ac2d;
        }
        if (param_4 == 0xa6) {
          local_28 = 3;
          local_24 = "exp10";
        }
        else {
          if (param_4 != 0xaa) {
            if (param_4 == 0xab) {
              local_24 = "log2";
              goto LAB_0100acae;
            }
            if (param_4 == 1000) {
              local_24 = "log";
            }
            else {
              if (param_4 != 0x3e9) goto LAB_0100ace2;
              local_24 = "log10";
            }
            goto LAB_0100acaa;
          }
          local_28 = 2;
          local_24 = "log2";
        }
        goto LAB_0100ac34;
      }
      local_24 = "exp";
    }
    else if (param_4 == 0x3eb) {
      local_24 = "atan";
    }
    else if (param_4 == 0x3ec) {
      local_24 = "ceil";
    }
    else if (param_4 == 0x3ed) {
      local_24 = "floor";
    }
    else {
      if (param_4 == 0x3ee) {
LAB_0100ac88:
        local_24 = "pow";
        goto LAB_0100acae;
      }
      if (param_4 != 0x3ef) goto LAB_0100ace2;
      local_24 = "modf";
    }
LAB_0100acaa:
    *param_3 = *param_1;
    goto LAB_0100acae;
  }
  if (param_4 == 0xa1) {
    local_28 = 3;
LAB_0100ac2d:
    local_24 = "exp2";
LAB_0100ac34:
    local_20 = *param_1;
    local_18 = *param_2;
    local_10 = *param_3;
    iVar2 = (*(code *)PTR_FUN_01011200)(&local_28);
    uVar1 = local_10;
    if (iVar2 == 0) {
      _DAT_01013060 = 0x22;
    }
  }
  else {
    if (param_4 < 0x19) {
      if (param_4 == 0x18) {
        local_28 = 3;
LAB_0100ab31:
        local_24 = "pow";
      }
      else if (param_4 == 2) {
        local_28 = 2;
        local_24 = "log";
      }
      else {
        if (param_4 == 3) {
          local_24 = "log";
LAB_0100acae:
          local_20 = *param_1;
          local_18 = *param_2;
          local_28 = 1;
          local_10 = *param_3;
          iVar2 = (*(code *)PTR_FUN_01011200)(&local_28);
          uVar1 = local_10;
          if (iVar2 == 0) {
            _DAT_01013060 = 0x21;
          }
          goto LAB_0100ace0;
        }
        if (param_4 == 8) {
          local_28 = 2;
          local_24 = "log10";
        }
        else {
          if (param_4 == 9) {
            local_24 = "log10";
            goto LAB_0100acae;
          }
          if (param_4 != 0xe) {
            if (param_4 != 0xf) goto LAB_0100ace2;
            local_24 = "exp";
            goto LAB_0100ab79;
          }
          local_28 = 3;
          local_24 = "exp";
        }
      }
      goto LAB_0100ac34;
    }
    if (param_4 == 0x19) {
      local_24 = "pow";
LAB_0100ab79:
      local_20 = *param_1;
      local_18 = *param_2;
      local_28 = 4;
      local_10 = *param_3;
      (*(code *)PTR_FUN_01011200)(&local_28);
      uVar1 = local_10;
    }
    else {
      if (param_4 != 0x1a) {
        if (param_4 != 0x1b) {
          if (param_4 == 0x1c) goto LAB_0100ac88;
          if (param_4 != 0x1d) goto LAB_0100ace2;
          local_24 = "pow";
          goto LAB_0100acaa;
        }
        local_28 = 2;
        goto LAB_0100ab31;
      }
      uVar1 = 0x3ff0000000000000;
    }
  }
LAB_0100ace0:
  *param_3 = uVar1;
LAB_0100ace2:
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_0100acf3 at 0100acf3
// ========================================================

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

undefined4 FUN_0100acf3(void)

{
  return 1;
}



// ========================================================
// Function: FUN_0100ad2d at 0100ad2d
// ========================================================

/* WARNING: Removing unreachable block (ram,0x0100ad50) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0100ad2d(void)

{
  uint uVar1;
  int iVar2;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  uint uVar3;
  uint local_8;
  
  uVar3 = (uint)(in_NT & 1) * 0x4000 | (uint)SBORROW4((int)&stack0xfffffffc,4) * 0x800 |
          (uint)(in_IF & 1) * 0x200 | (uint)(in_TF & 1) * 0x100 | (uint)((int)&local_8 < 0) * 0x80 |
          (uint)(&stack0x00000000 == (undefined1 *)0x8) * 0x40 | (uint)(in_AF & 1) * 0x10 |
          (uint)((POPCOUNT((uint)&local_8 & 0xff) & 1U) == 0) * 4 |
          (uint)(&stack0xfffffffc < (undefined1 *)0x4) | (uint)(in_ID & 1) * 0x200000 |
          (uint)(in_VIP & 1) * 0x100000 | (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000
  ;
  uVar1 = uVar3 ^ 0x200000;
  local_8 = 0;
  if (((uint)((uVar1 & 0x4000) != 0) * 0x4000 | (uint)((uVar1 & 0x800) != 0) * 0x800 |
       (uint)((uVar1 & 0x200) != 0) * 0x200 | (uint)((uVar1 & 0x100) != 0) * 0x100 |
       (uint)((uVar1 & 0x80) != 0) * 0x80 | (uint)((uVar1 & 0x40) != 0) * 0x40 |
       (uint)((uVar1 & 0x10) != 0) * 0x10 | (uint)((uVar1 & 4) != 0) * 4 | (uint)((uVar1 & 1) != 0)
       | (uint)((uVar1 & 0x200000) != 0) * 0x200000 | (uint)((uVar1 & 0x40000) != 0) * 0x40000) !=
      uVar3) {
    iVar2 = cpuid_Version_info(1);
    local_8 = *(uint *)(iVar2 + 8);
  }
  _DAT_01013524 = 0;
  DAT_01013520 = 0;
  if (((local_8 & 0x4000000) != 0) && (iVar2 = FUN_0100acf3(), iVar2 != 0)) {
    _DAT_01013524 = 1;
  }
  return 0;
}



// ========================================================
// Function: FUN_0100ae70 at 0100ae70
// ========================================================

void FUN_0100ae70(void)

{
  float10 in_ST0;
  
  FUN_0100ae8e(SUB84((double)in_ST0,0),(uint)((ulonglong)(double)in_ST0 >> 0x20));
  return;
}



// ========================================================
// Function: FUN_0100ae8e at 0100ae8e
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl FUN_0100ae8e(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  double in_XMM0_Qa;
  double dVar3;
  double dVar4;
  double dVar5;
  undefined2 uStack_c;
  undefined6 uStack_a;
  undefined2 uStack_4;
  
  uVar1 = (ushort)((ulonglong)in_XMM0_Qa >> 0x30) & 0x7fff;
  if ((0x408f - uVar1 | uVar1 - 0x3c90) < 0x80000000) {
    dVar4 = _DAT_01001b80 * in_XMM0_Qa + _DAT_01001b60;
    dVar5 = (_UNK_01001b88 * in_XMM0_Qa + _UNK_01001b68) - _UNK_01001b68;
    uVar1 = SUB84(dVar4,0);
    iVar2 = (uVar1 & 0x3f) * 0x10;
    dVar3 = (in_XMM0_Qa - _DAT_01001b90 * (dVar4 - _DAT_01001b60)) -
            _DAT_01001ba0 * (dVar4 - _DAT_01001b60);
    dVar5 = (in_XMM0_Qa - _UNK_01001b98 * dVar5) - _UNK_01001ba8 * dVar5;
    dVar4 = (double)(*(ulonglong *)(&UNK_01001bd8 + iVar2) |
                    ((ulonglong)dVar4 & _DAT_01001b40) + _DAT_01001b50 << 0x2e);
    dVar3 = dVar5 * dVar5 * (_UNK_01001bc8 + _UNK_01001bb8 * dVar5) +
            dVar3 + *(double *)(&DAT_01001bd0 + iVar2) +
            dVar3 * dVar3 * dVar3 * dVar3 * (_DAT_01001bc0 + _DAT_01001bb0 * dVar3);
    if (((int)uVar1 >> 6) + 0x37eU < 0x77d) {
      return (float10)(dVar3 * dVar4 + dVar4);
    }
    dVar5 = (double)(~_DAT_01001b30 & (ulonglong)dVar4 |
                    (ulonglong)(((int)uVar1 >> 7) + 0x3ff) << 0x34);
    uStack_4 = (undefined2)((ulonglong)dVar5 >> 0x30);
    in_XMM0_Qa = (double)((ulonglong)((((int)uVar1 >> 6) - ((int)uVar1 >> 7)) + 0x3ff) << 0x34) *
                 (dVar5 + dVar3 * dVar5);
    if (((ushort)((ulonglong)in_XMM0_Qa >> 0x30) & 0x7ff0) < 0x7ff0) {
      if (((ulonglong)in_XMM0_Qa & 0x7ff0000000000000) != 0) goto LAB_0100b082;
      iVar2 = 0xf;
    }
    else {
      iVar2 = 0xe;
    }
  }
  else {
    uVar1 = param_2 & 0x7fffffff;
    if (uVar1 < 0x40900000) {
      return (float10)((double)CONCAT44(param_2,param_1) + _DAT_01001fd0);
    }
    if (uVar1 < 0x7ff00000) {
      if (param_2 < 0x80000000) {
        in_XMM0_Qa = DAT_01002000 * DAT_01002000;
        iVar2 = 0xe;
      }
      else {
        in_XMM0_Qa = DAT_01002008 * DAT_01002008;
        iVar2 = 0xf;
      }
    }
    else {
      if ((uVar1 < 0x7ff00001) && (param_1 == 0)) {
        if (param_2 != 0x7ff00000) {
          return (float10)_DAT_01001ff8;
        }
        return (float10)_DAT_01001ff0;
      }
      iVar2 = 0x3ea;
    }
  }
  uStack_c = SUB82(in_XMM0_Qa,0);
  uStack_a = (undefined6)((ulonglong)in_XMM0_Qa >> 0x10);
  FUN_0100aa7b((undefined8 *)&param_1,(undefined8 *)&param_1,(undefined8 *)&uStack_c,iVar2);
  in_XMM0_Qa = (double)CONCAT62(uStack_a,uStack_c);
LAB_0100b082:
  return (float10)in_XMM0_Qa;
}



// ========================================================
// Function: FUN_0100b28e at 0100b28e
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined5 __fastcall FUN_0100b28e(undefined4 param_1,undefined1 param_2)

{
  undefined4 extraout_EAX;
  undefined4 in_EAX;
  undefined1 extraout_DL;
  int unaff_EBP;
  float10 in_ST0;
  float10 fVar1;
  float10 fVar2;
  undefined4 unaff_retaddr;
  
  fVar1 = ABS(in_ST0);
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(_DAT_0101122e < fVar1) << 8 | (ushort)(NAN(_DAT_0101122e) || NAN(fVar1)) << 10 |
       (ushort)(_DAT_0101122e == fVar1) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 0x41) == 0) {
    fVar2 = ROUND(in_ST0);
    fVar1 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar2 < fVar1) << 8 | (ushort)(NAN(fVar2) || NAN(fVar1)) << 10 |
         (ushort)(fVar2 == fVar1) << 0xe;
    fVar2 = in_ST0 - fVar2;
    fVar1 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar2 < fVar1) << 8 | (ushort)(NAN(fVar2) || NAN(fVar1)) << 10 |
         (ushort)(fVar2 == fVar1) << 0xe;
    f2xm1(ABS(fVar2));
    return CONCAT14(*(undefined1 *)(unaff_EBP + -0x9f),in_EAX);
  }
  fVar1 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(in_ST0 < fVar1) << 8 | (ushort)(NAN(in_ST0) || NAN(fVar1)) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 1) == 0) {
    return CONCAT14(param_2,unaff_retaddr);
  }
  *(undefined1 *)(unaff_EBP + -0x90) = 4;
  FUN_0100e306();
  return CONCAT14(extraout_DL,extraout_EAX);
}



// ========================================================
// Function: __cintrindisp2 at 0100b340
// ========================================================

/* Library Function - Single Match
    __cintrindisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __fastcall __cintrindisp2(undefined4 param_1,int param_2)

{
  __trandisp2(param_1,param_2);
  DAT_010131e8 = 1;
  FUN_0100b3f5();
  return;
}



// ========================================================
// Function: __cintrindisp1 at 0100b37e
// ========================================================

/* Library Function - Single Match
    __cintrindisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __fastcall __cintrindisp1(undefined4 param_1,int param_2)

{
  __trandisp1(param_1,param_2);
  DAT_010131e8 = 1;
  FUN_0100b3f5();
  return;
}



// ========================================================
// Function: __ctrandisp2 at 0100b3b4
// ========================================================

/* Library Function - Single Match
    __ctrandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cdecl __ctrandisp2(uint param_1,int param_2,uint param_3,int param_4)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  
  __fload(param_1,param_2);
  __fload(param_3,param_4);
  __trandisp2(extraout_ECX,extraout_EDX);
  FUN_0100b3ee();
  return;
}



// ========================================================
// Function: FUN_0100b3ee at 0100b3ee
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0100b3ee(void)

{
  char cVar1;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  DAT_010131e8 = '\0';
  if (DAT_01013058 != 0) {
    DAT_010131e8 = 0;
    return;
  }
  _DAT_010131e0 = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if (cVar1 != -1) {
      if (cVar1 != -2) {
        if (cVar1 == '\0') {
          DAT_010131e8 = 0;
          return;
        }
        *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
        goto LAB_0100b4d8;
      }
      if (((ulonglong)_DAT_010131e0 & 0x7ff0000000000000) == 0) {
        *(undefined4 *)(unaff_EBP + -0x8e) = 4;
        in_ST0 = (float10)fscale(in_ST0,(float10)_DAT_01002038);
        if (ABS(in_ST0) < (float10)_DAT_01002028) {
          in_ST0 = in_ST0 * (float10)_DAT_01002048;
        }
        goto LAB_0100b4d8;
      }
    }
    if ((DAT_010131e6 & 0x7ff0) == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)_DAT_01002030);
      if ((float10)_DAT_01002020 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)_DAT_01002040;
      }
      goto LAB_0100b4d8;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    DAT_010131e8 = 0;
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    DAT_010131e8 = 0;
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_0100b4d8:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if (DAT_010131e8 == '\0') {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_0100e5ad((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),(int *)(unaff_EBP + -0x8e),
               (ushort *)(unaff_EBP + -0xa4));
  return;
}



// ========================================================
// Function: FUN_0100b3f5 at 0100b3f5
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0100b3f5(void)

{
  char cVar1;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  if (DAT_01013058 != 0) {
    return;
  }
  _DAT_010131e0 = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if (cVar1 != -1) {
      if (cVar1 != -2) {
        if (cVar1 == '\0') {
          return;
        }
        *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
        goto LAB_0100b4d8;
      }
      if (((ulonglong)_DAT_010131e0 & 0x7ff0000000000000) == 0) {
        *(undefined4 *)(unaff_EBP + -0x8e) = 4;
        in_ST0 = (float10)fscale(in_ST0,(float10)_DAT_01002038);
        if (ABS(in_ST0) < (float10)_DAT_01002028) {
          in_ST0 = in_ST0 * (float10)_DAT_01002048;
        }
        goto LAB_0100b4d8;
      }
    }
    if ((DAT_010131e6 & 0x7ff0) == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)_DAT_01002030);
      if ((float10)_DAT_01002020 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)_DAT_01002040;
      }
      goto LAB_0100b4d8;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_0100b4d8:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if (DAT_010131e8 == '\0') {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_0100e5ad((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),(int *)(unaff_EBP + -0x8e),
               (ushort *)(unaff_EBP + -0xa4));
  return;
}



// ========================================================
// Function: __ctrandisp1 at 0100b53a
// ========================================================

/* Library Function - Single Match
    __ctrandisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cdecl __ctrandisp1(uint param_1,int param_2)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  
  __fload(param_1,param_2);
  __trandisp1(extraout_ECX,extraout_EDX);
  FUN_0100b3ee();
  return;
}



// ========================================================
// Function: __fload at 0100b566
// ========================================================

/* Library Function - Single Match
    __fload
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

float10 __cdecl __fload(uint param_1,int param_2)

{
  float10 fVar1;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    fVar1 = (float10)CONCAT28(param_2._2_2_ | 0x7fff,
                              CONCAT44(param_2 << 0xb | param_1 >> 0x15,param_1));
  }
  else {
    fVar1 = (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
  }
  return fVar1;
}



// ========================================================
// Function: ___crtMessageBoxA at 0100b5a7
// ========================================================

/* Library Function - Single Match
    ___crtMessageBoxA
   
   Library: Visual Studio 2003 Release */

int __cdecl ___crtMessageBoxA(LPCSTR _LpText,LPCSTR _LpCaption,UINT _UType)

{
  HMODULE hModule;
  int iVar1;
  int iVar2;
  undefined1 local_14 [8];
  byte local_c;
  undefined1 local_8 [4];
  
  iVar2 = 0;
  if (DAT_010131ec == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if ((hModule == (HMODULE)0x0) ||
       (DAT_010131ec = GetProcAddress(hModule,"MessageBoxA"), DAT_010131ec == (FARPROC)0x0)) {
      return 0;
    }
    DAT_010131f0 = GetProcAddress(hModule,"GetActiveWindow");
    DAT_010131f4 = GetProcAddress(hModule,"GetLastActivePopup");
    if ((DAT_0101306c == 2) &&
       (DAT_010131fc = GetProcAddress(hModule,"GetUserObjectInformationA"),
       DAT_010131fc != (FARPROC)0x0)) {
      DAT_010131f8 = GetProcAddress(hModule,"GetProcessWindowStation");
    }
  }
  if ((DAT_010131f8 == (FARPROC)0x0) ||
     (((iVar1 = (*DAT_010131f8)(), iVar1 != 0 &&
       (iVar1 = (*DAT_010131fc)(iVar1,1,local_14,0xc,local_8), iVar1 != 0)) && ((local_c & 1) != 0))
     )) {
    if (((DAT_010131f0 != (FARPROC)0x0) && (iVar2 = (*DAT_010131f0)(), iVar2 != 0)) &&
       (DAT_010131f4 != (FARPROC)0x0)) {
      iVar2 = (*DAT_010131f4)(iVar2);
    }
  }
  else if (DAT_01013078 < 4) {
    _UType = _UType | 0x40000;
  }
  else {
    _UType = _UType | 0x200000;
  }
  iVar2 = (*DAT_010131ec)(iVar2,_LpText,_LpCaption,_UType);
  return iVar2;
}



// ========================================================
// Function: _strncpy at 0100b6b0
// ========================================================

/* Library Function - Single Match
    _strncpy
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strncpy(char *_Dest,char *_Source,size_t _Count)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (_Count == 0) {
    return _Dest;
  }
  puVar5 = (uint *)_Dest;
  if (((uint)_Source & 3) != 0) {
    while( true ) {
      uVar4 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
      if (_Count == 0) {
        return _Dest;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)_Source & 3) == 0) {
        uVar4 = _Count >> 2;
        goto joined_r0x0100b6ee;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = _Count >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_0100b72b;
        goto LAB_0100b799;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
    } while (_Count != 0);
    return _Dest;
  }
  uVar4 = _Count >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *(uint *)_Source;
      uVar2 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 4);
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x0100b795:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_0100b799:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          _Count = _Count & 3;
          if (_Count != 0) goto LAB_0100b72b;
          return _Dest;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x0100b795;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x0100b795;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x0100b795;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x0100b6ee:
    } while (uVar4 != 0);
    _Count = _Count & 3;
    if (_Count == 0) {
      return _Dest;
    }
  }
  do {
    cVar3 = (char)*(uint *)_Source;
    _Source = (char *)((int)_Source + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (_Count = _Count - 1, _Count != 0) {
LAB_0100b72b:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return _Dest;
    }
    _Count = _Count - 1;
  } while (_Count != 0);
  return _Dest;
}



// ========================================================
// Function: FUN_0100b7b3 at 0100b7b3
// ========================================================

undefined4 __cdecl FUN_0100b7b3(byte param_1,uint param_2,byte param_3)

{
  uint uVar1;
  
  if ((*(byte *)((int)&DAT_01013300 + param_1 + 1) & param_3) == 0) {
    if (param_2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = *(ushort *)(&DAT_010020c2 + (uint)param_1 * 2) & param_2;
    }
    if (uVar1 == 0) {
      return 0;
    }
  }
  return 1;
}



// ========================================================
// Function: FUN_0100b7ec at 0100b7ec
// ========================================================

void __cdecl FUN_0100b7ec(byte param_1)

{
  FUN_0100b7b3(param_1,0,4);
  return;
}



// ========================================================
// Function: _CPtoLCID at 0100b807
// ========================================================

/* Library Function - Single Match
    _CPtoLCID
   
   Library: Visual Studio 2003 Release */

undefined4 _CPtoLCID(void)

{
  int in_EAX;
  
  if (in_EAX == 0x3a4) {
    return 0x411;
  }
  if (in_EAX == 0x3a8) {
    return 0x804;
  }
  if (in_EAX == 0x3b5) {
    return 0x412;
  }
  if (in_EAX != 0x3b6) {
    return 0;
  }
  return 0x404;
}



// ========================================================
// Function: setSBCS at 0100b83b
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _setSBCS
   
   Library: Visual Studio 2003 Release */

void __cdecl setSBCS(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_01013300;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_01013404 = 0;
  _DAT_010132e0 = 0;
  DAT_010132dc = 0;
  DAT_01013410 = 0;
  DAT_01013414 = 0;
  DAT_01013418 = 0;
  return;
}



// ========================================================
// Function: FUN_0100b86b at 0100b86b
// ========================================================

void FUN_0100b86b(void)

{
  byte *pbVar1;
  BOOL BVar2;
  uint uVar3;
  CHAR CVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  BYTE *pBVar8;
  CHAR *pCVar9;
  _cpinfo local_51c;
  WORD local_508 [256];
  CHAR local_308 [256];
  CHAR local_208 [256];
  CHAR local_108 [256];
  uint local_8;
  
  local_8 = DAT_0101107c;
  BVar2 = GetCPInfo(DAT_01013404,&local_51c);
  if (BVar2 == 1) {
    uVar3 = 0;
    do {
      local_108[uVar3] = (CHAR)uVar3;
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
    local_108[0] = ' ';
    if (local_51c.LeadByte[0] != 0) {
      pBVar8 = local_51c.LeadByte + 1;
      do {
        uVar3 = (uint)local_51c.LeadByte[0];
        if (uVar3 <= *pBVar8) {
          uVar6 = (*pBVar8 - uVar3) + 1;
          uVar7 = uVar6 >> 2;
          pCVar9 = local_108 + uVar3;
          while (uVar7 != 0) {
            uVar7 = uVar7 - 1;
            builtin_memcpy(pCVar9,"    ",4);
            pCVar9 = pCVar9 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pCVar9 = ' ';
            pCVar9 = pCVar9 + 1;
          }
        }
        local_51c.LeadByte[0] = pBVar8[1];
        pBVar8 = pBVar8 + 2;
      } while (local_51c.LeadByte[0] != 0);
    }
    FUN_0100eabe(1,local_108,0x100,local_508,DAT_01013404,DAT_010132dc,0);
    FUN_0100e6ed(DAT_010132dc,0x100,local_108,0x100,local_208,0x100,DAT_01013404,0);
    FUN_0100e6ed(DAT_010132dc,0x200,local_108,0x100,local_308,0x100,DAT_01013404,0);
    uVar3 = 0;
    do {
      if ((local_508[uVar3] & 1) == 0) {
        if ((local_508[uVar3] & 2) != 0) {
          pbVar1 = (byte *)((int)&DAT_01013300 + uVar3 + 1);
          *pbVar1 = *pbVar1 | 0x20;
          CVar4 = local_308[uVar3];
          goto LAB_0100b988;
        }
        (&DAT_01013420)[uVar3] = 0;
      }
      else {
        pbVar1 = (byte *)((int)&DAT_01013300 + uVar3 + 1);
        *pbVar1 = *pbVar1 | 0x10;
        CVar4 = local_208[uVar3];
LAB_0100b988:
        (&DAT_01013420)[uVar3] = CVar4;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
  }
  else {
    uVar3 = 0;
    do {
      if ((uVar3 < 0x41) || (0x5a < uVar3)) {
        if ((0x60 < uVar3) && (uVar3 < 0x7b)) {
          pbVar1 = (byte *)((int)&DAT_01013300 + uVar3 + 1);
          *pbVar1 = *pbVar1 | 0x20;
          cVar5 = (char)uVar3 + -0x20;
          goto LAB_0100b9cb;
        }
        (&DAT_01013420)[uVar3] = 0;
      }
      else {
        pbVar1 = (byte *)((int)&DAT_01013300 + uVar3 + 1);
        *pbVar1 = *pbVar1 | 0x10;
        cVar5 = (char)uVar3 + ' ';
LAB_0100b9cb:
        (&DAT_01013420)[uVar3] = cVar5;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
  }
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: __setmbcp at 0100ba07
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __setmbcp
   
   Library: Visual Studio 2003 Release */

int __cdecl __setmbcp(int _CodePage)

{
  BYTE *pBVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  BOOL BVar6;
  uint uVar7;
  BYTE *pBVar8;
  int iVar9;
  int extraout_ECX;
  int iVar10;
  byte *pbVar11;
  byte *pbVar12;
  undefined4 *puVar13;
  uint local_20;
  _cpinfo local_1c;
  uint local_8;
  
  local_8 = DAT_0101107c;
  DAT_01013200 = 0;
  if (_CodePage == -2) {
    DAT_01013200 = 1;
    _CodePage = GetOEMCP();
  }
  else if (_CodePage == -3) {
    DAT_01013200 = 1;
    _CodePage = GetACP();
  }
  else if (_CodePage == -4) {
    DAT_01013200 = 1;
    _CodePage = DAT_010132a0;
  }
  if (_CodePage == DAT_01013404) goto LAB_0100bbe2;
  if (_CodePage != 0) {
    iVar10 = 0;
    uVar5 = 0;
LAB_0100ba84:
    if (*(int *)((int)&DAT_01011288 + uVar5) != _CodePage) goto code_r0x0100ba8c;
    puVar13 = &DAT_01013300;
    for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar13 = 0;
      puVar13 = puVar13 + 1;
    }
    local_20 = 0;
    *(undefined1 *)puVar13 = 0;
    pbVar11 = (byte *)(iVar10 * 0x30 + 0x1011298);
    do {
      bVar4 = *pbVar11;
      pbVar12 = pbVar11;
      while ((bVar4 != 0 && (bVar3 = pbVar12[1], bVar3 != 0))) {
        uVar5 = (uint)bVar4;
        if (uVar5 <= bVar3) {
          bVar4 = (&DAT_01011280)[local_20];
          do {
            pbVar2 = (byte *)((int)&DAT_01013300 + uVar5 + 1);
            *pbVar2 = *pbVar2 | bVar4;
            uVar5 = uVar5 + 1;
          } while (uVar5 <= bVar3);
        }
        pbVar12 = pbVar12 + 2;
        bVar4 = *pbVar12;
      }
      local_20 = local_20 + 1;
      pbVar11 = pbVar11 + 8;
    } while (local_20 < 4);
    DAT_01013404 = _CodePage;
    _DAT_010132e0 = 1;
    DAT_010132dc = _CPtoLCID();
    DAT_01013410 = *(undefined4 *)(&DAT_0101128c + extraout_ECX);
    DAT_01013414 = *(undefined4 *)(&DAT_01011290 + extraout_ECX);
    DAT_01013418 = *(undefined4 *)(&DAT_01011294 + extraout_ECX);
    goto LAB_0100bbd6;
  }
LAB_0100bbd1:
  setSBCS();
LAB_0100bbd6:
  FUN_0100b86b();
LAB_0100bbe2:
  iVar10 = FUN_01008e6b(local_8);
  return iVar10;
code_r0x0100ba8c:
  uVar5 = uVar5 + 0x30;
  iVar10 = iVar10 + 1;
  if (0xef < uVar5) goto code_r0x0100ba97;
  goto LAB_0100ba84;
code_r0x0100ba97:
  BVar6 = GetCPInfo(_CodePage,&local_1c);
  if (BVar6 != 1) {
    if (DAT_01013200 == 0) goto LAB_0100bbe2;
    goto LAB_0100bbd1;
  }
  puVar13 = &DAT_01013300;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  *(undefined1 *)puVar13 = 0;
  uVar5 = 1;
  DAT_010132dc = 0;
  DAT_01013404 = _CodePage;
  if (local_1c.MaxCharSize < 2) {
    _DAT_010132e0 = 0;
  }
  else {
    if (local_1c.LeadByte[0] != '\0') {
      pBVar8 = local_1c.LeadByte + 1;
      do {
        bVar4 = *pBVar8;
        if (bVar4 == 0) break;
        for (uVar7 = (uint)pBVar8[-1]; uVar7 <= bVar4; uVar7 = uVar7 + 1) {
          pbVar11 = (byte *)((int)&DAT_01013300 + uVar7 + 1);
          *pbVar11 = *pbVar11 | 4;
        }
        pBVar1 = pBVar8 + 1;
        pBVar8 = pBVar8 + 2;
      } while (*pBVar1 != 0);
    }
    do {
      pbVar11 = (byte *)((int)&DAT_01013300 + uVar5 + 1);
      *pbVar11 = *pbVar11 | 8;
      uVar5 = uVar5 + 1;
    } while (uVar5 < 0xff);
    DAT_010132dc = _CPtoLCID();
    _DAT_010132e0 = 1;
  }
  DAT_01013410 = 0;
  DAT_01013414 = 0;
  DAT_01013418 = 0;
  goto LAB_0100bbd6;
}



// ========================================================
// Function: ___initmbctable at 0100bbf4
// ========================================================

/* Library Function - Single Match
    ___initmbctable
   
   Library: Visual Studio 2003 Release */

undefined4 ___initmbctable(void)

{
  if (DAT_0101364c == 0) {
    __setmbcp(-3);
    DAT_0101364c = 1;
  }
  return 0;
}



// ========================================================
// Function: FUN_0100bc17 at 0100bc17
// ========================================================

undefined4 __cdecl FUN_0100bc17(undefined4 param_1)

{
  DAT_010132c8 = HeapAlloc(DAT_01013528,0,0x140);
  if (DAT_010132c8 == (LPVOID)0x0) {
    return 0;
  }
  DAT_010132c0 = 0;
  DAT_010132c4 = 0;
  DAT_010132d0 = DAT_010132c8;
  DAT_010132cc = param_1;
  DAT_010132d4 = 0x10;
  return 1;
}



// ========================================================
// Function: FUN_0100bc6a at 0100bc6a
// ========================================================

uint __cdecl FUN_0100bc6a(int param_1)

{
  uint uVar1;
  
  uVar1 = DAT_010132c8;
  while( true ) {
    if (DAT_010132c8 + DAT_010132c4 * 0x14 <= uVar1) {
      return 0;
    }
    if ((uint)(param_1 - *(int *)(uVar1 + 0xc)) < 0x100000) break;
    uVar1 = uVar1 + 0x14;
  }
  return uVar1;
}



// ========================================================
// Function: ___sbh_free_block at 0100bc9f
// ========================================================

/* Library Function - Single Match
    ___sbh_free_block
   
   Library: Visual Studio 2003 Release */

void __cdecl ___sbh_free_block(uint *param_1,int param_2)

{
  int *piVar1;
  char *pcVar2;
  uint *puVar3;
  int *piVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  uint uVar9;
  uint *puVar10;
  uint *puVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  uint local_8;
  
  uVar6 = param_1[4];
  puVar12 = (uint *)(param_2 + -4);
  uVar14 = param_2 - param_1[3] >> 0xf;
  piVar4 = (int *)(uVar14 * 0x204 + 0x144 + uVar6);
  local_8 = *puVar12 - 1;
  if ((local_8 & 1) == 0) {
    puVar10 = (uint *)(local_8 + (int)puVar12);
    uVar13 = *puVar10;
    uVar7 = *(uint *)(param_2 + -8);
    if ((uVar13 & 1) == 0) {
      uVar9 = ((int)uVar13 >> 4) - 1;
      if (0x3f < uVar9) {
        uVar9 = 0x3f;
      }
      if (puVar10[1] == puVar10[2]) {
        if (uVar9 < 0x20) {
          pcVar2 = (char *)(uVar9 + 4 + uVar6);
          uVar9 = ~(0x80000000U >> ((byte)uVar9 & 0x1f));
          puVar11 = (uint *)(uVar6 + 0x44 + uVar14 * 4);
          *puVar11 = *puVar11 & uVar9;
          *pcVar2 = *pcVar2 + -1;
          if (*pcVar2 == '\0') {
            *param_1 = *param_1 & uVar9;
          }
        }
        else {
          pcVar2 = (char *)(uVar9 + 4 + uVar6);
          uVar9 = ~(0x80000000U >> ((byte)uVar9 - 0x20 & 0x1f));
          puVar11 = (uint *)(uVar6 + 0xc4 + uVar14 * 4);
          *puVar11 = *puVar11 & uVar9;
          *pcVar2 = *pcVar2 + -1;
          if (*pcVar2 == '\0') {
            param_1[1] = param_1[1] & uVar9;
          }
        }
      }
      local_8 = local_8 + uVar13;
      *(uint *)(puVar10[2] + 4) = puVar10[1];
      *(uint *)(puVar10[1] + 8) = puVar10[2];
    }
    puVar10 = (uint *)(((int)local_8 >> 4) - 1);
    if ((uint *)0x3f < puVar10) {
      puVar10 = (uint *)0x3f;
    }
    puVar11 = param_1;
    if ((uVar7 & 1) == 0) {
      puVar12 = (uint *)((int)puVar12 - uVar7);
      puVar11 = (uint *)(((int)uVar7 >> 4) - 1);
      if ((uint *)0x3f < puVar11) {
        puVar11 = (uint *)0x3f;
      }
      local_8 = local_8 + uVar7;
      puVar10 = (uint *)(((int)local_8 >> 4) - 1);
      if ((uint *)0x3f < puVar10) {
        puVar10 = (uint *)0x3f;
      }
      if (puVar11 != puVar10) {
        if (puVar12[1] == puVar12[2]) {
          if (puVar11 < (uint *)0x20) {
            uVar13 = ~(0x80000000U >> ((byte)puVar11 & 0x1f));
            puVar3 = (uint *)(uVar6 + 0x44 + uVar14 * 4);
            *puVar3 = *puVar3 & uVar13;
            pcVar2 = (char *)((int)puVar11 + uVar6 + 4);
            *pcVar2 = *pcVar2 + -1;
            if (*pcVar2 == '\0') {
              *param_1 = *param_1 & uVar13;
            }
          }
          else {
            uVar13 = ~(0x80000000U >> ((byte)puVar11 - 0x20 & 0x1f));
            puVar3 = (uint *)(uVar6 + 0xc4 + uVar14 * 4);
            *puVar3 = *puVar3 & uVar13;
            pcVar2 = (char *)((int)puVar11 + uVar6 + 4);
            *pcVar2 = *pcVar2 + -1;
            if (*pcVar2 == '\0') {
              param_1[1] = param_1[1] & uVar13;
            }
          }
        }
        *(uint *)(puVar12[2] + 4) = puVar12[1];
        *(uint *)(puVar12[1] + 8) = puVar12[2];
      }
    }
    if (((uVar7 & 1) != 0) || (puVar11 != puVar10)) {
      piVar1 = piVar4 + (int)puVar10 * 2;
      uVar13 = piVar1[1];
      puVar12[2] = (uint)piVar1;
      puVar12[1] = uVar13;
      piVar1[1] = (int)puVar12;
      *(uint **)(puVar12[1] + 8) = puVar12;
      if (puVar12[1] == puVar12[2]) {
        cVar5 = *(char *)((int)puVar10 + uVar6 + 4);
        *(char *)((int)puVar10 + uVar6 + 4) = cVar5 + '\x01';
        bVar8 = (byte)puVar10;
        if (puVar10 < (uint *)0x20) {
          if (cVar5 == '\0') {
            *param_1 = *param_1 | 0x80000000U >> (bVar8 & 0x1f);
          }
          puVar10 = (uint *)(uVar6 + 0x44 + uVar14 * 4);
          *puVar10 = *puVar10 | 0x80000000U >> (bVar8 & 0x1f);
        }
        else {
          if (cVar5 == '\0') {
            param_1[1] = param_1[1] | 0x80000000U >> (bVar8 - 0x20 & 0x1f);
          }
          puVar10 = (uint *)(uVar6 + 0xc4 + uVar14 * 4);
          *puVar10 = *puVar10 | 0x80000000U >> (bVar8 - 0x20 & 0x1f);
        }
      }
    }
    *puVar12 = local_8;
    *(uint *)((local_8 - 4) + (int)puVar12) = local_8;
    *piVar4 = *piVar4 + -1;
    if (*piVar4 == 0) {
      if (DAT_010132c0 != (uint *)0x0) {
        VirtualFree((LPVOID)(DAT_010132d8 * 0x8000 + DAT_010132c0[3]),0x8000,0x4000);
        DAT_010132c0[2] = DAT_010132c0[2] | 0x80000000U >> ((byte)DAT_010132d8 & 0x1f);
        *(undefined4 *)(DAT_010132c0[4] + 0xc4 + DAT_010132d8 * 4) = 0;
        *(char *)(DAT_010132c0[4] + 0x43) = *(char *)(DAT_010132c0[4] + 0x43) + -1;
        if (*(char *)(DAT_010132c0[4] + 0x43) == '\0') {
          DAT_010132c0[1] = DAT_010132c0[1] & 0xfffffffe;
        }
        if (DAT_010132c0[2] == 0xffffffff) {
          VirtualFree((LPVOID)DAT_010132c0[3],0,0x8000);
          HeapFree(DAT_01013528,0,(LPVOID)DAT_010132c0[4]);
          FUN_0100d020(DAT_010132c0,DAT_010132c0 + 5,
                       (DAT_010132c4 * 0x14 - (int)DAT_010132c0) + -0x14 + DAT_010132c8);
          DAT_010132c4 = DAT_010132c4 + -1;
          if (DAT_010132c0 < param_1) {
            param_1 = param_1 + -5;
          }
          DAT_010132d0 = DAT_010132c8;
        }
      }
      DAT_010132c0 = param_1;
      DAT_010132d8 = uVar14;
    }
  }
  return;
}



// ========================================================
// Function: ___sbh_alloc_new_region at 0100bfbe
// ========================================================

/* Library Function - Single Match
    ___sbh_alloc_new_region
   
   Library: Visual Studio 2003 Release */

undefined4 * ___sbh_alloc_new_region(void)

{
  undefined4 *puVar1;
  LPVOID pvVar2;
  
  if (DAT_010132c4 == DAT_010132d4) {
    pvVar2 = HeapReAlloc(DAT_01013528,0,DAT_010132c8,(DAT_010132d4 * 5 + 0x50) * 4);
    if (pvVar2 == (LPVOID)0x0) {
      return (undefined4 *)0x0;
    }
    DAT_010132d4 = DAT_010132d4 + 0x10;
    DAT_010132c8 = pvVar2;
  }
  puVar1 = (undefined4 *)((int)DAT_010132c8 + DAT_010132c4 * 0x14);
  pvVar2 = HeapAlloc(DAT_01013528,8,0x41c4);
  puVar1[4] = pvVar2;
  if (pvVar2 != (LPVOID)0x0) {
    pvVar2 = VirtualAlloc((LPVOID)0x0,0x100000,0x2000,4);
    puVar1[3] = pvVar2;
    if (pvVar2 != (LPVOID)0x0) {
      puVar1[2] = 0xffffffff;
      *puVar1 = 0;
      puVar1[1] = 0;
      DAT_010132c4 = DAT_010132c4 + 1;
      *(undefined4 *)puVar1[4] = 0xffffffff;
      return puVar1;
    }
    HeapFree(DAT_01013528,0,(LPVOID)puVar1[4]);
  }
  return (undefined4 *)0x0;
}



// ========================================================
// Function: ___sbh_alloc_new_group at 0100c07a
// ========================================================

/* Library Function - Single Match
    ___sbh_alloc_new_group
   
   Library: Visual Studio 2003 Release */

int __cdecl ___sbh_alloc_new_group(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  LPVOID pvVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  LPVOID lpAddress;
  
  iVar2 = *(int *)(param_1 + 0x10);
  iVar8 = 0;
  for (iVar3 = *(int *)(param_1 + 8); -1 < iVar3; iVar3 = iVar3 << 1) {
    iVar8 = iVar8 + 1;
  }
  iVar3 = iVar8 * 0x204 + 0x144 + iVar2;
  iVar7 = 0x3f;
  iVar4 = iVar3;
  do {
    *(int *)(iVar4 + 8) = iVar4;
    *(int *)(iVar4 + 4) = iVar4;
    iVar4 = iVar4 + 8;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  lpAddress = (LPVOID)(iVar8 * 0x8000 + *(int *)(param_1 + 0xc));
  pvVar5 = VirtualAlloc(lpAddress,0x8000,0x1000,4);
  if (pvVar5 == (LPVOID)0x0) {
    iVar8 = -1;
  }
  else {
    if (lpAddress <= (LPVOID)((int)lpAddress + 0x7000U)) {
      piVar6 = (int *)((int)lpAddress + 0x10);
      iVar7 = ((uint)((int)((int)lpAddress + 0x7000U) - (int)lpAddress) >> 0xc) + 1;
      do {
        piVar6[-2] = -1;
        piVar6[0x3fb] = -1;
        *piVar6 = (int)(piVar6 + 0x3ff);
        piVar6[-1] = 0xff0;
        piVar6[1] = (int)(piVar6 + -0x401);
        piVar6[0x3fa] = 0xff0;
        piVar6 = piVar6 + 0x400;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    *(int *)(iVar3 + 0x1fc) = (int)lpAddress + 0xc;
    *(int *)((int)lpAddress + 0x14) = iVar3 + 0x1f8;
    *(int *)(iVar3 + 0x200) = (int)lpAddress + 0x700c;
    *(int *)((int)lpAddress + 0x7010) = iVar3 + 0x1f8;
    *(undefined4 *)(iVar2 + 0x44 + iVar8 * 4) = 0;
    *(undefined4 *)(iVar2 + 0xc4 + iVar8 * 4) = 1;
    cVar1 = *(char *)(iVar2 + 0x43);
    *(char *)(iVar2 + 0x43) = cVar1 + '\x01';
    if (cVar1 == '\0') {
      *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 1;
    }
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~(0x80000000U >> ((byte)iVar8 & 0x1f));
  }
  return iVar8;
}



// ========================================================
// Function: ___sbh_resize_block at 0100c187
// ========================================================

/* Library Function - Single Match
    ___sbh_resize_block
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

undefined4 __cdecl ___sbh_resize_block(uint *param_1,int param_2,int param_3)

{
  char *pcVar1;
  uint *puVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  char cVar6;
  uint uVar7;
  uint *puVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint local_c;
  
  uVar7 = param_1[4];
  uVar10 = param_2 - param_1[3] >> 0xf;
  iVar5 = uVar10 * 0x204 + 0x144 + uVar7;
  uVar12 = param_3 + 0x17U & 0xfffffff0;
  iVar9 = *(int *)(param_2 + -4) + -1;
  puVar8 = (uint *)(*(int *)(param_2 + -4) + -5 + param_2);
  uVar13 = *puVar8;
  if (iVar9 < (int)uVar12) {
    if (((uVar13 & 1) != 0) || ((int)(uVar13 + iVar9) < (int)uVar12)) {
      return 0;
    }
    local_c = ((int)uVar13 >> 4) - 1;
    if (0x3f < local_c) {
      local_c = 0x3f;
    }
    if (puVar8[1] == puVar8[2]) {
      if (local_c < 0x20) {
        pcVar1 = (char *)(local_c + 4 + uVar7);
        uVar11 = ~(0x80000000U >> ((byte)local_c & 0x1f));
        puVar2 = (uint *)(uVar7 + 0x44 + uVar10 * 4);
        *puVar2 = *puVar2 & uVar11;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          *param_1 = *param_1 & uVar11;
        }
      }
      else {
        pcVar1 = (char *)(local_c + 4 + uVar7);
        uVar11 = ~(0x80000000U >> ((byte)local_c - 0x20 & 0x1f));
        puVar2 = (uint *)(uVar7 + 0xc4 + uVar10 * 4);
        *puVar2 = *puVar2 & uVar11;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          param_1[1] = param_1[1] & uVar11;
        }
      }
    }
    *(uint *)(puVar8[2] + 4) = puVar8[1];
    *(uint *)(puVar8[1] + 8) = puVar8[2];
    iVar9 = uVar13 + (iVar9 - uVar12);
    if (0 < iVar9) {
      uVar13 = (iVar9 >> 4) - 1;
      iVar3 = param_2 + -4 + uVar12;
      if (0x3f < uVar13) {
        uVar13 = 0x3f;
      }
      iVar5 = iVar5 + uVar13 * 8;
      *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar5 + 4);
      *(int *)(iVar3 + 8) = iVar5;
      *(int *)(iVar5 + 4) = iVar3;
      *(int *)(*(int *)(iVar3 + 4) + 8) = iVar3;
      if (*(int *)(iVar3 + 4) == *(int *)(iVar3 + 8)) {
        cVar6 = *(char *)(uVar13 + 4 + uVar7);
        *(char *)(uVar13 + 4 + uVar7) = cVar6 + '\x01';
        if (uVar13 < 0x20) {
          if (cVar6 == '\0') {
            *param_1 = *param_1 | 0x80000000U >> ((byte)uVar13 & 0x1f);
          }
          puVar8 = (uint *)(uVar7 + 0x44 + uVar10 * 4);
        }
        else {
          if (cVar6 == '\0') {
            param_1[1] = param_1[1] | 0x80000000U >> ((byte)uVar13 - 0x20 & 0x1f);
          }
          puVar8 = (uint *)(uVar7 + 0xc4 + uVar10 * 4);
          uVar13 = uVar13 - 0x20;
        }
        *puVar8 = *puVar8 | 0x80000000U >> ((byte)uVar13 & 0x1f);
      }
      piVar4 = (int *)(param_2 + -4 + uVar12);
      *piVar4 = iVar9;
      *(int *)(iVar9 + -4 + (int)piVar4) = iVar9;
    }
    *(uint *)(param_2 + -4) = uVar12 + 1;
    *(uint *)(param_2 + -8 + uVar12) = uVar12 + 1;
  }
  else if ((int)uVar12 < iVar9) {
    param_3 = iVar9 - uVar12;
    *(uint *)(param_2 + -4) = uVar12 + 1;
    piVar4 = (int *)(param_2 + -4 + uVar12);
    uVar11 = (param_3 >> 4) - 1;
    piVar4[-1] = uVar12 + 1;
    if (0x3f < uVar11) {
      uVar11 = 0x3f;
    }
    if ((uVar13 & 1) == 0) {
      uVar12 = ((int)uVar13 >> 4) - 1;
      if (0x3f < uVar12) {
        uVar12 = 0x3f;
      }
      if (puVar8[1] == puVar8[2]) {
        if (uVar12 < 0x20) {
          pcVar1 = (char *)(uVar12 + 4 + uVar7);
          uVar12 = ~(0x80000000U >> ((byte)uVar12 & 0x1f));
          puVar2 = (uint *)(uVar7 + 0x44 + uVar10 * 4);
          *puVar2 = *puVar2 & uVar12;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            *param_1 = *param_1 & uVar12;
          }
        }
        else {
          pcVar1 = (char *)(uVar12 + 4 + uVar7);
          uVar12 = ~(0x80000000U >> ((byte)uVar12 - 0x20 & 0x1f));
          puVar2 = (uint *)(uVar7 + 0xc4 + uVar10 * 4);
          *puVar2 = *puVar2 & uVar12;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            param_1[1] = param_1[1] & uVar12;
          }
        }
      }
      *(uint *)(puVar8[2] + 4) = puVar8[1];
      *(uint *)(puVar8[1] + 8) = puVar8[2];
      param_3 = param_3 + uVar13;
      uVar11 = (param_3 >> 4) - 1;
      if (0x3f < uVar11) {
        uVar11 = 0x3f;
      }
    }
    iVar5 = iVar5 + uVar11 * 8;
    iVar9 = *(int *)(iVar5 + 4);
    piVar4[2] = iVar5;
    piVar4[1] = iVar9;
    *(int **)(iVar5 + 4) = piVar4;
    *(int **)(piVar4[1] + 8) = piVar4;
    if (piVar4[1] == piVar4[2]) {
      cVar6 = *(char *)(uVar11 + 4 + uVar7);
      *(char *)(uVar11 + 4 + uVar7) = cVar6 + '\x01';
      if (uVar11 < 0x20) {
        if (cVar6 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> ((byte)uVar11 & 0x1f);
        }
        puVar8 = (uint *)(uVar7 + 0x44 + uVar10 * 4);
      }
      else {
        if (cVar6 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> ((byte)uVar11 - 0x20 & 0x1f);
        }
        puVar8 = (uint *)(uVar7 + 0xc4 + uVar10 * 4);
        uVar11 = uVar11 - 0x20;
      }
      *puVar8 = *puVar8 | 0x80000000U >> ((byte)uVar11 & 0x1f);
    }
    *piVar4 = param_3;
    *(int *)(param_3 + -4 + (int)piVar4) = param_3;
  }
  return 1;
}



// ========================================================
// Function: ___sbh_alloc_block at 0100c46d
// ========================================================

/* Library Function - Single Match
    ___sbh_alloc_block
   
   Library: Visual Studio 2003 Release */

int * __cdecl ___sbh_alloc_block(uint *param_1)

{
  int *piVar1;
  char *pcVar2;
  int *piVar3;
  char cVar4;
  int *piVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  int iVar10;
  int *piVar11;
  uint *puVar12;
  uint *puVar13;
  uint uVar14;
  int iVar15;
  uint local_c;
  int local_8;
  
  uVar7 = (int)param_1 + 0x17U & 0xfffffff0;
  iVar8 = ((int)((int)param_1 + 0x17U) >> 4) + -1;
  puVar9 = DAT_010132c8 + DAT_010132c4 * 5;
  bVar6 = (byte)iVar8;
  param_1 = DAT_010132d0;
  if (iVar8 < 0x20) {
    uVar14 = 0xffffffff >> (bVar6 & 0x1f);
    local_c = 0xffffffff;
  }
  else {
    uVar14 = 0;
    local_c = 0xffffffff >> (bVar6 - 0x20 & 0x1f);
  }
  for (; (param_1 < puVar9 && ((param_1[1] & local_c) == 0 && (*param_1 & uVar14) == 0));
      param_1 = param_1 + 5) {
  }
  puVar12 = DAT_010132c8;
  if (param_1 == puVar9) {
    for (; (puVar12 < DAT_010132d0 && ((puVar12[1] & local_c) == 0 && (*puVar12 & uVar14) == 0));
        puVar12 = puVar12 + 5) {
    }
    param_1 = puVar12;
    if (puVar12 == DAT_010132d0) {
      for (; (puVar12 < puVar9 && (puVar12[2] == 0)); puVar12 = puVar12 + 5) {
      }
      puVar13 = DAT_010132c8;
      param_1 = puVar12;
      if (puVar12 == puVar9) {
        for (; (puVar13 < DAT_010132d0 && (puVar13[2] == 0)); puVar13 = puVar13 + 5) {
        }
        param_1 = puVar13;
        if ((puVar13 == DAT_010132d0) &&
           (param_1 = ___sbh_alloc_new_region(), param_1 == (uint *)0x0)) {
          return (int *)0x0;
        }
      }
      iVar8 = ___sbh_alloc_new_group((int)param_1);
      *(int *)param_1[4] = iVar8;
      if (*(int *)param_1[4] == -1) {
        return (int *)0x0;
      }
    }
  }
  piVar5 = (int *)param_1[4];
  local_8 = *piVar5;
  if ((local_8 == -1) ||
     ((piVar5[local_8 + 0x31] & local_c) == 0 && (piVar5[local_8 + 0x11] & uVar14) == 0)) {
    local_8 = 0;
    puVar9 = (uint *)(piVar5 + 0x11);
    if ((piVar5[0x31] & local_c) == 0 && (*puVar9 & uVar14) == 0) {
      do {
        puVar12 = puVar9 + 0x21;
        local_8 = local_8 + 1;
        puVar9 = puVar9 + 1;
      } while ((*puVar12 & local_c) == 0 && (*puVar9 & uVar14) == 0);
    }
  }
  piVar3 = piVar5 + local_8 * 0x81 + 0x51;
  iVar8 = 0;
  uVar14 = piVar5[local_8 + 0x11] & uVar14;
  if (uVar14 == 0) {
    uVar14 = piVar5[local_8 + 0x31] & local_c;
    iVar8 = 0x20;
  }
  for (; -1 < (int)uVar14; uVar14 = uVar14 << 1) {
    iVar8 = iVar8 + 1;
  }
  piVar11 = (int *)piVar3[iVar8 * 2 + 1];
  iVar10 = *piVar11 - uVar7;
  iVar15 = (iVar10 >> 4) + -1;
  if (0x3f < iVar15) {
    iVar15 = 0x3f;
  }
  DAT_010132d0 = param_1;
  if (iVar15 != iVar8) {
    if (piVar11[1] == piVar11[2]) {
      if (iVar8 < 0x20) {
        pcVar2 = (char *)((int)piVar5 + iVar8 + 4);
        uVar14 = ~(0x80000000U >> ((byte)iVar8 & 0x1f));
        piVar5[local_8 + 0x11] = uVar14 & piVar5[local_8 + 0x11];
        *pcVar2 = *pcVar2 + -1;
        if (*pcVar2 == '\0') {
          *param_1 = *param_1 & uVar14;
        }
      }
      else {
        pcVar2 = (char *)((int)piVar5 + iVar8 + 4);
        uVar14 = ~(0x80000000U >> ((byte)iVar8 - 0x20 & 0x1f));
        piVar5[local_8 + 0x31] = piVar5[local_8 + 0x31] & uVar14;
        *pcVar2 = *pcVar2 + -1;
        if (*pcVar2 == '\0') {
          param_1[1] = param_1[1] & uVar14;
        }
      }
    }
    *(int *)(piVar11[2] + 4) = piVar11[1];
    *(int *)(piVar11[1] + 8) = piVar11[2];
    if (iVar10 == 0) goto LAB_0100c728;
    piVar1 = piVar3 + iVar15 * 2;
    iVar8 = piVar1[1];
    piVar11[2] = (int)piVar1;
    piVar11[1] = iVar8;
    piVar1[1] = (int)piVar11;
    *(int **)(piVar11[1] + 8) = piVar11;
    if (piVar11[1] == piVar11[2]) {
      cVar4 = *(char *)(iVar15 + 4 + (int)piVar5);
      *(char *)(iVar15 + 4 + (int)piVar5) = cVar4 + '\x01';
      bVar6 = (byte)iVar15;
      if (iVar15 < 0x20) {
        if (cVar4 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> (bVar6 & 0x1f);
        }
        piVar5[local_8 + 0x11] = piVar5[local_8 + 0x11] | 0x80000000U >> (bVar6 & 0x1f);
      }
      else {
        if (cVar4 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> (bVar6 - 0x20 & 0x1f);
        }
        piVar5[local_8 + 0x31] = piVar5[local_8 + 0x31] | 0x80000000U >> (bVar6 - 0x20 & 0x1f);
      }
    }
  }
  if (iVar10 != 0) {
    *piVar11 = iVar10;
    *(int *)(iVar10 + -4 + (int)piVar11) = iVar10;
  }
LAB_0100c728:
  piVar11 = (int *)((int)piVar11 + iVar10);
  *piVar11 = uVar7 + 1;
  *(uint *)((int)piVar11 + (uVar7 - 4)) = uVar7 + 1;
  iVar8 = *piVar3;
  *piVar3 = iVar8 + 1;
  if (((iVar8 == 0) && (param_1 == DAT_010132c0)) && (local_8 == DAT_010132d8)) {
    DAT_010132c0 = (uint *)0x0;
  }
  *piVar5 = local_8;
  return piVar11 + 1;
}



// ========================================================
// Function: __global_unwind2 at 0100c770
// ========================================================

/* Library Function - Single Match
    __global_unwind2
   
   Library: Visual Studio */

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x100c788,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}



// ========================================================
// Function: FUN_0100c7cb at 0100c7cb
// ========================================================

void __cdecl FUN_0100c7cb(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  void *pvStack_20;
  undefined1 *puStack_1c;
  undefined4 local_18;
  int iStack_14;
  
  iStack_14 = param_1;
  puStack_1c = &LAB_0100c790;
  pvStack_20 = ExceptionList;
  ExceptionList = &pvStack_20;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    uVar2 = *(uint *)(param_1 + 0xc);
    if ((uVar2 == 0xffffffff) || ((param_2 != 0xffffffff && (uVar2 <= param_2)))) break;
    local_18 = *(undefined4 *)(iVar1 + uVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_18;
    if (*(int *)(iVar1 + 4 + uVar2 * 0xc) == 0) {
      FUN_0100c867();
      (**(code **)(iVar1 + 8 + uVar2 * 0xc))();
    }
  }
  ExceptionList = pvStack_20;
  return;
}



// ========================================================
// Function: FUN_0100c867 at 0100c867
// ========================================================

undefined4 FUN_0100c867(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_01011380 = *(undefined4 *)(unaff_EBP + 8);
  DAT_0101137c = in_EAX;
  DAT_01011384 = unaff_EBP;
  return in_EAX;
}



// ========================================================
// Function: FUN_0100c88a at 0100c88a
// ========================================================

undefined4 __cdecl FUN_0100c88a(void *param_1)

{
  uint *puVar1;
  void *pvVar2;
  uint uVar3;
  void *pvVar4;
  uint *puVar5;
  SIZE_T SVar6;
  int *piVar7;
  LONG LVar8;
  uint *puVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  _MEMORY_BASIC_INFORMATION local_24;
  void *local_8;
  
  pvVar4 = param_1;
  puVar9 = *(uint **)((int)param_1 + 8);
  if ((((uint)puVar9 & 3) != 0) ||
     ((local_8 = StackLimit, StackLimit <= puVar9 && (puVar9 < StackBase)))) {
    return 0;
  }
  puVar1 = (uint *)((int)param_1 + 0xc);
  if (*puVar1 == 0xffffffff) {
    return 1;
  }
  uVar11 = 0;
  param_1 = (void *)0x0;
  puVar5 = puVar9;
  do {
    if ((*puVar5 != 0xffffffff) && (uVar11 <= *puVar5)) {
      return 0;
    }
    if (puVar5[1] != 0) {
      param_1 = (void *)((int)param_1 + 1);
    }
    uVar11 = uVar11 + 1;
    puVar5 = puVar5 + 3;
  } while (uVar11 <= *puVar1);
  if ((param_1 != (void *)0x0) &&
     ((pvVar2 = *(void **)((int)pvVar4 + -8), pvVar2 < StackLimit || (pvVar4 <= pvVar2)))) {
    return 0;
  }
  uVar11 = (uint)puVar9 & 0xfffff000;
  iVar14 = 0;
  if (0 < DAT_01013208) {
    do {
      if ((&DAT_01013210)[iVar14] == uVar11) {
        if (iVar14 < 1) {
          return 1;
        }
        LVar8 = InterlockedExchange((LONG *)&DAT_01013250,1);
        if (LVar8 != 0) {
          return 1;
        }
        if ((&DAT_01013210)[iVar14] == uVar11) goto LAB_0100ca88;
        iVar14 = DAT_01013208 + -1;
        if (iVar14 < 0) goto LAB_0100ca76;
        goto LAB_0100ca66;
      }
      iVar14 = iVar14 + 1;
    } while (iVar14 < DAT_01013208);
  }
  SVar6 = VirtualQuery(puVar9,&local_24,0x1c);
  if (SVar6 == 0) {
    return 0xffffffff;
  }
  if (local_24.Type != 0x1000000) {
    return 0xffffffff;
  }
  if (((byte)local_24.Protect & 0xcc) != 0) {
    if (((*(short *)local_24.AllocationBase != 0x5a4d) ||
        (piVar7 = (int *)(*(int *)((int)local_24.AllocationBase + 0x3c) +
                         (int)local_24.AllocationBase), *piVar7 != 0x4550)) ||
       ((short)piVar7[6] != 0x10b)) {
      return 0xffffffff;
    }
    uVar10 = (uint)*(ushort *)(piVar7 + 5);
    if (*(short *)((int)piVar7 + 6) == 0) {
      return 0xffffffff;
    }
    uVar3 = *(uint *)((int)piVar7 + uVar10 + 0x24);
    if (((uVar3 <= (uint)((int)puVar9 - (int)local_24.AllocationBase)) &&
        ((uint)((int)puVar9 - (int)local_24.AllocationBase) <
         *(int *)((int)piVar7 + uVar10 + 0x20) + uVar3)) &&
       ((*(byte *)((int)piVar7 + uVar10 + 0x3f) & 0x80) != 0)) {
      return 0;
    }
  }
  LVar8 = InterlockedExchange((LONG *)&DAT_01013250,1);
  iVar14 = DAT_01013208;
  if (LVar8 != 0) {
    return 1;
  }
  iVar12 = DAT_01013208;
  if (0 < DAT_01013208) {
    puVar9 = (uint *)(&DAT_0101320c + DAT_01013208 * 4);
    do {
      if (*puVar9 == uVar11) break;
      iVar12 = iVar12 + -1;
      puVar9 = puVar9 + -1;
    } while (0 < iVar12);
  }
  if (iVar12 == 0) {
    iVar12 = 0xf;
    if (DAT_01013208 < 0x10) {
      iVar12 = DAT_01013208;
    }
    iVar13 = 0;
    if (-1 < iVar12) {
      do {
        puVar9 = &DAT_01013210 + iVar13;
        uVar10 = *puVar9;
        iVar13 = iVar13 + 1;
        *puVar9 = uVar11;
        uVar11 = uVar10;
      } while (iVar13 <= iVar12);
    }
    if (iVar14 < 0x10) {
      DAT_01013208 = iVar14 + 1;
    }
  }
  InterlockedExchange((LONG *)&DAT_01013250,0);
  return 1;
  while (iVar14 = iVar14 + -1, -1 < iVar14) {
LAB_0100ca66:
    if ((&DAT_01013210)[iVar14] == uVar11) break;
  }
  if (iVar14 < 0) {
LAB_0100ca76:
    if (DAT_01013208 < 0x10) {
      DAT_01013208 = DAT_01013208 + 1;
    }
    iVar14 = DAT_01013208 + -1;
  }
  else if (iVar14 == 0) goto LAB_0100caa0;
LAB_0100ca88:
  iVar12 = 0;
  if (-1 < iVar14) {
    do {
      puVar9 = &DAT_01013210 + iVar12;
      uVar10 = *puVar9;
      iVar12 = iVar12 + 1;
      *puVar9 = uVar11;
      uVar11 = uVar10;
    } while (iVar12 <= iVar14);
  }
LAB_0100caa0:
  InterlockedExchange((LONG *)&DAT_01013250,0);
  return 1;
}



// ========================================================
// Function: __isctype at 0100cabb
// ========================================================

/* Library Function - Single Match
    __isctype
   
   Library: Visual Studio 2003 Release */

int __cdecl __isctype(int _C,int _Type)

{
  undefined4 uVar1;
  int iVar2;
  BOOL BVar3;
  undefined4 in_ECX;
  undefined4 local_8;
  
  if (_C + 1U < 0x101) {
    _C._2_2_ = *(ushort *)(PTR_DAT_01011394 + _C * 2);
  }
  else {
    local_8._2_2_ = (undefined2)((uint)in_ECX >> 0x10);
    if ((PTR_DAT_01011394[(_C >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      local_8._0_2_ = (ushort)(byte)_C;
      iVar2 = 1;
    }
    else {
      local_8 = CONCAT31(CONCAT21(local_8._2_2_,(byte)_C),(char)((uint)_C >> 8));
      uVar1 = local_8;
      local_8._3_1_ = (undefined1)((uint)in_ECX >> 0x18);
      local_8._0_2_ = (ushort)uVar1;
      local_8._0_3_ = (uint3)(ushort)local_8;
      iVar2 = 2;
    }
    BVar3 = FUN_0100eabe(1,(LPCSTR)&local_8,iVar2,(LPWORD)((int)&_C + 2),DAT_010132a0,DAT_01013290,1
                        );
    if (BVar3 == 0) {
      return 0;
    }
  }
  return (uint)_C._2_2_ & _Type;
}



// ========================================================
// Function: _tolower at 0100cb40
// ========================================================

/* Library Function - Single Match
    _tolower
   
   Library: Visual Studio 2003 Release */

int __cdecl _tolower(int _C)

{
  uint uVar1;
  int iVar2;
  uint in_ECX;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((DAT_01013290 == 0) || ((DAT_01011530 != 0 && ((uint)_C < 0x80)))) {
    if ((0x40 < _C) && (_C < 0x5b)) {
      return _C + 0x20;
    }
  }
  else {
    local_c = in_ECX;
    local_8 = in_ECX;
    if ((uint)_C < 0x100) {
      if (DAT_01011388 < 2) {
        uVar1 = (byte)PTR_DAT_01011394[_C * 2] & 1;
      }
      else {
        uVar1 = __isctype(_C,1);
      }
      if (uVar1 == 0) {
        return _C;
      }
    }
    uVar1 = local_8;
    if ((PTR_DAT_01011394[(_C >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      local_8._0_2_ = (ushort)(byte)_C;
      iVar2 = 1;
    }
    else {
      local_8._0_2_ = CONCAT11((byte)_C,(char)((uint)_C >> 8));
      local_8._3_1_ = SUB41(uVar1,3);
      local_8._0_3_ = (uint3)(ushort)local_8;
      iVar2 = 2;
    }
    uVar1 = FUN_0100e6ed(DAT_01013290,0x100,(LPCSTR)&local_8,iVar2,(LPSTR)&local_c,3,DAT_010132a0,1)
    ;
    if (uVar1 != 0) {
      if (uVar1 != 1) {
        return (uint)CONCAT11((CHAR)local_c,local_c._1_1_);
      }
      return local_c & 0xff;
    }
  }
  return _C;
}



// ========================================================
// Function: FUN_0100cc1c at 0100cc1c
// ========================================================

undefined4 __cdecl FUN_0100cc1c(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_2 / 0x20;
  uVar1 = *(uint *)(param_1 + iVar2 * 4) & ~(-1 << (0x1fU - (char)(param_2 % 0x20) & 0x1f));
  while( true ) {
    if (uVar1 != 0) {
      return 0;
    }
    iVar2 = iVar2 + 1;
    if (2 < iVar2) break;
    uVar1 = *(uint *)(param_1 + iVar2 * 4);
  }
  return 1;
}



// ========================================================
// Function: FUN_0100cc58 at 0100cc58
// ========================================================

void __cdecl FUN_0100cc58(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  
  puVar3 = (uint *)(param_1 + (param_2 / 0x20) * 4);
  iVar1 = ___addl(*puVar3,1 << (0x1fU - (char)(param_2 % 0x20) & 0x1f),puVar3);
  iVar2 = param_2 / 0x20 + -1;
  if (-1 < iVar2) {
    puVar3 = (uint *)(param_1 + iVar2 * 4);
    do {
      if (iVar1 == 0) {
        return;
      }
      iVar1 = ___addl(*puVar3,1,puVar3);
      iVar2 = iVar2 + -1;
      puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
  }
  return;
}



// ========================================================
// Function: __RoundMan at 0100ccae
// ========================================================

/* Library Function - Single Match
    __RoundMan
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl __RoundMan(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  undefined4 *puVar5;
  undefined4 local_8;
  
  local_8 = 0;
  iVar2 = param_2 / 0x20;
  bVar4 = 0x1f - (char)(param_2 % 0x20);
  if (((*(uint *)(param_1 + iVar2 * 4) & 1 << (bVar4 & 0x1f)) != 0) &&
     (iVar3 = FUN_0100cc1c(param_1,param_2), iVar3 == 0)) {
    local_8 = FUN_0100cc58(param_1,param_2 + -1);
  }
  puVar1 = (uint *)(param_1 + iVar2 * 4);
  *puVar1 = *puVar1 & -1 << (bVar4 & 0x1f);
  iVar2 = iVar2 + 1;
  if (iVar2 < 3) {
    puVar5 = (undefined4 *)(param_1 + iVar2 * 4);
    for (iVar3 = 3 - iVar2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  return local_8;
}



// ========================================================
// Function: __CopyMan at 0100cd27
// ========================================================

/* Library Function - Single Match
    __CopyMan
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

void __cdecl __CopyMan(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 3;
  iVar1 = param_1 - (int)param_2;
  do {
    *(undefined4 *)(iVar1 + (int)param_2) = *param_2;
    param_2 = param_2 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



// ========================================================
// Function: __IsZeroMan at 0100cd4b
// ========================================================

/* Library Function - Single Match
    __IsZeroMan
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

undefined4 __cdecl __IsZeroMan(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*(int *)(param_1 + iVar1 * 4) != 0) {
      return 0;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 3);
  return 1;
}



// ========================================================
// Function: __ShrMan at 0100cd6f
// ========================================================

/* Library Function - Single Match
    __ShrMan
   
   Library: Visual Studio 2003 Release */

void __cdecl __ShrMan(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  undefined4 *puVar4;
  uint local_8;
  
  bVar3 = (byte)(param_2 % 0x20);
  iVar2 = 0;
  local_8 = 0;
  do {
    uVar1 = *(uint *)(param_1 + iVar2 * 4);
    *(uint *)(param_1 + iVar2 * 4) = uVar1 >> (bVar3 & 0x1f) | local_8;
    local_8 = (uVar1 & ~(-1 << (bVar3 & 0x1f))) << (0x20 - bVar3 & 0x1f);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 3);
  iVar2 = 2;
  puVar4 = (undefined4 *)(param_1 + (2 - param_2 / 0x20) * 4);
  do {
    if (iVar2 < param_2 / 0x20) {
      *(undefined4 *)(param_1 + iVar2 * 4) = 0;
    }
    else {
      *(undefined4 *)(param_1 + iVar2 * 4) = *puVar4;
    }
    iVar2 = iVar2 + -1;
    puVar4 = puVar4 + -1;
  } while (-1 < iVar2);
  return;
}



// ========================================================
// Function: __ld12cvt at 0100cdf1
// ========================================================

/* Library Function - Single Match
    __ld12cvt
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl __ld12cvt(ushort *param_1,uint *param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 local_1c [3];
  uint local_10;
  uint local_c;
  int local_8;
  
  uVar1 = param_1[5];
  local_10 = *(uint *)(param_1 + 3);
  local_c = *(uint *)(param_1 + 1);
  local_8 = (uint)*param_1 << 0x10;
  uVar4 = uVar1 & 0x7fff;
  iVar5 = uVar4 - 0x3fff;
  if (iVar5 == -0x3fff) {
    iVar5 = 0;
    iVar2 = __IsZeroMan((int)&local_10);
    if (iVar2 != 0) {
LAB_0100cf0b:
      uVar3 = 0;
      goto LAB_0100cf0d;
    }
    local_10 = 0;
    local_c = 0;
  }
  else {
    __CopyMan((int)local_1c,&local_10);
    iVar2 = __RoundMan((int)&local_10,param_3[2]);
    if (iVar2 != 0) {
      iVar5 = uVar4 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar5 < iVar2 - param_3[2]) {
      local_10 = 0;
      local_c = 0;
    }
    else {
      if (iVar2 < iVar5) {
        if (*param_3 <= iVar5) {
          local_c = 0;
          local_8 = 0;
          local_10 = 0x80000000;
          __ShrMan((int)&local_10,param_3[3]);
          iVar5 = param_3[5] + *param_3;
          uVar3 = 1;
          goto LAB_0100cf0d;
        }
        local_10 = local_10 & 0x7fffffff;
        iVar5 = param_3[5] + iVar5;
        __ShrMan((int)&local_10,param_3[3]);
        goto LAB_0100cf0b;
      }
      __CopyMan((int)&local_10,local_1c);
      __ShrMan((int)&local_10,iVar2 - iVar5);
      __RoundMan((int)&local_10,param_3[2]);
      __ShrMan((int)&local_10,param_3[3] + 1);
    }
  }
  iVar5 = 0;
  uVar3 = 2;
LAB_0100cf0d:
  local_10 = iVar5 << (0x1fU - (char)param_3[3] & 0x1f) |
             -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 | local_10;
  if (param_3[4] == 0x40) {
    param_2[1] = local_10;
    *param_2 = local_c;
  }
  else if (param_3[4] == 0x20) {
    *param_2 = local_10;
  }
  return uVar3;
}



// ========================================================
// Function: FUN_0100cf50 at 0100cf50
// ========================================================

void __cdecl FUN_0100cf50(ushort *param_1,uint *param_2)

{
  __ld12cvt(param_1,param_2,(int *)&DAT_0101139c);
  return;
}



// ========================================================
// Function: FUN_0100cf6f at 0100cf6f
// ========================================================

void __cdecl FUN_0100cf6f(ushort *param_1,uint *param_2)

{
  __ld12cvt(param_1,param_2,(int *)&DAT_010113b4);
  return;
}



// ========================================================
// Function: FUN_0100cf8e at 0100cf8e
// ========================================================

void __cdecl FUN_0100cf8e(uint *param_1,byte *param_2)

{
  int local_18;
  ushort local_14 [6];
  uint local_8;
  
  local_8 = DAT_0101107c;
  FUN_0100ee6f(local_14,&local_18,param_2,0,0,0,0);
  FUN_0100cf50(local_14,param_1);
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_0100cfd6 at 0100cfd6
// ========================================================

void __cdecl FUN_0100cfd6(uint *param_1,byte *param_2)

{
  int local_18;
  ushort local_14 [6];
  uint local_8;
  
  local_8 = DAT_0101107c;
  FUN_0100ee6f(local_14,&local_18,param_2,0,0,0,0);
  FUN_0100cf6f(local_14,param_1);
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_0100d020 at 0100d020
// ========================================================

undefined4 * __cdecl FUN_0100d020(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    puVar3 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar4 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = param_3 >> 2;
      uVar2 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return param_1;
        case 2:
          goto switchD_0100d1d7_caseD_2;
        case 3:
          goto switchD_0100d1d7_caseD_3;
        }
        goto switchD_0100d1d7_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_0100d1d7_caseD_0;
      case 1:
        goto switchD_0100d1d7_caseD_1;
      case 2:
        goto switchD_0100d1d7_caseD_2;
      case 3:
        goto switchD_0100d1d7_caseD_3;
      default:
        uVar1 = param_3 - ((uint)puVar4 & 3);
        switch((uint)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          puVar3 = (undefined4 *)((int)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (undefined4 *)((int)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_0100d1d7_caseD_2;
            case 3:
              goto switchD_0100d1d7_caseD_3;
            }
            goto switchD_0100d1d7_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          puVar3 = (undefined4 *)((int)puVar3 + -2);
          puVar4 = (undefined4 *)((int)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_0100d1d7_caseD_2;
            case 3:
              goto switchD_0100d1d7_caseD_3;
            }
            goto switchD_0100d1d7_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + -3);
          puVar4 = (undefined4 *)((int)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_0100d1d7_caseD_2;
            case 3:
              goto switchD_0100d1d7_caseD_3;
            }
            goto switchD_0100d1d7_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_0100d1d7_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return param_1;
    case 2:
switchD_0100d1d7_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return param_1;
    case 3:
switchD_0100d1d7_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return param_1;
    }
switchD_0100d1d7_caseD_0:
    return param_1;
  }
  puVar3 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    uVar2 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *param_2;
        param_2 = param_2 + 1;
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return param_1;
      case 2:
        goto switchD_0100d055_caseD_2;
      case 3:
        goto switchD_0100d055_caseD_3;
      }
      goto switchD_0100d055_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_0100d055_caseD_0;
    case 1:
      goto switchD_0100d055_caseD_1;
    case 2:
      goto switchD_0100d055_caseD_2;
    case 3:
      goto switchD_0100d055_caseD_3;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar3 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_0100d055_caseD_2;
          case 3:
            goto switchD_0100d055_caseD_3;
          }
          goto switchD_0100d055_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar3 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_0100d055_caseD_2;
          case 3:
            goto switchD_0100d055_caseD_3;
          }
          goto switchD_0100d055_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_0100d055_caseD_2;
          case 3:
            goto switchD_0100d055_caseD_3;
          }
          goto switchD_0100d055_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar3[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar3[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar3[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar3[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar3[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar3[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_0100d055_caseD_1:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    return param_1;
  case 2:
switchD_0100d055_caseD_2:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
switchD_0100d055_caseD_3:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
switchD_0100d055_caseD_0:
  return param_1;
}



// ========================================================
// Function: _strlen at 0100d360
// ========================================================

/* Library Function - Single Match
    _strlen
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

size_t __cdecl _strlen(char *_Str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)_Str;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_0100d380;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_0100d3b3:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_0100d380:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (int)puVar3 - (int)_Str;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (size_t)((int)puVar3 + (1 - (int)_Str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (size_t)((int)puVar3 + (2 - (int)_Str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_0100d3b3;
}



// ========================================================
// Function: FID_conflict:__mbscpy at 0100d3e0
// ========================================================

/* Library Function - Multiple Matches With Different Base Names
    __mbscpy
    _strcpy
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl FID_conflict___mbscpy(char *_Dest,char *_Source)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = (uint *)_Dest;
  while (((uint)_Source & 3) != 0) {
    bVar1 = (byte)*(uint *)_Source;
    uVar3 = (uint)bVar1;
    _Source = (char *)((int)_Source + 1);
    if (bVar1 == 0) goto LAB_0100d4c8;
    *(byte *)puVar4 = bVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
  }
  do {
    uVar2 = *(uint *)_Source;
    uVar3 = *(uint *)_Source;
    _Source = (char *)((int)_Source + 4);
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar3 == '\0') {
LAB_0100d4c8:
        *(byte *)puVar4 = (byte)uVar3;
        return _Dest;
      }
      if ((char)(uVar3 >> 8) == '\0') {
        *(short *)puVar4 = (short)uVar3;
        return _Dest;
      }
      if ((uVar3 & 0xff0000) == 0) {
        *(short *)puVar4 = (short)uVar3;
        *(byte *)((int)puVar4 + 2) = 0;
        return _Dest;
      }
      if ((uVar3 & 0xff000000) == 0) {
        *puVar4 = uVar3;
        return _Dest;
      }
    }
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
  } while( true );
}



// ========================================================
// Function: FUN_0100d4d5 at 0100d4d5
// ========================================================

void __cdecl FUN_0100d4d5(char *param_1,int param_2,int param_3)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char cVar5;
  
  pcVar2 = param_1;
  pcVar4 = *(char **)(param_3 + 0xc);
  pcVar1 = param_1 + 1;
  *param_1 = '0';
  pcVar3 = pcVar1;
  if (0 < param_2) {
    param_1 = (char *)param_2;
    param_2 = 0;
    do {
      cVar5 = *pcVar4;
      if (cVar5 == '\0') {
        cVar5 = '0';
      }
      else {
        pcVar4 = pcVar4 + 1;
      }
      *pcVar3 = cVar5;
      pcVar3 = pcVar3 + 1;
      param_1 = param_1 + -1;
    } while (param_1 != (char *)0x0);
  }
  *pcVar3 = '\0';
  if ((-1 < param_2) && ('4' < *pcVar4)) {
    while (pcVar3 = pcVar3 + -1, *pcVar3 == '9') {
      *pcVar3 = '0';
    }
    *pcVar3 = *pcVar3 + '\x01';
  }
  if (*pcVar2 == '1') {
    *(int *)(param_3 + 4) = *(int *)(param_3 + 4) + 1;
  }
  else {
    pcVar4 = pcVar1;
    do {
      cVar5 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar5 != '\0');
    FUN_0100d020((undefined4 *)pcVar2,(undefined4 *)pcVar1,(uint)(pcVar4 + (1 - (int)(pcVar2 + 2))))
    ;
  }
  return;
}



// ========================================================
// Function: ___dtold at 0100d55b
// ========================================================

/* Library Function - Single Match
    ___dtold
   
   Library: Visual Studio 2003 Release */

void __cdecl ___dtold(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  uint local_8;
  
  uVar1 = *(ushort *)((int)param_2 + 6);
  local_8 = 0x80000000;
  uVar3 = uVar1 >> 4;
  uVar4 = uVar3 & 0x7ff;
  uVar2 = *param_2;
  if ((uVar3 & 0x7ff) == 0) {
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    uVar4 = uVar4 + 0x3c01;
    local_8 = 0;
  }
  else if (uVar4 == 0x7ff) {
    uVar4 = 0x7fff;
  }
  else {
    uVar4 = uVar4 + 0x3c00;
  }
  param_1[1] = uVar2 >> 0x15 | (param_2[1] & 0xfffff) << 0xb | local_8;
  *param_1 = uVar2 << 0xb;
  while (local_8 == 0) {
    uVar2 = param_1[1];
    uVar4 = uVar4 - 1;
    param_1[1] = uVar2 << 1 | *param_1 >> 0x1f;
    *param_1 = *param_1 * 2;
    local_8 = uVar2 << 1 & 0x80000000;
  }
  *(ushort *)(param_1 + 2) = uVar1 & 0x8000 | uVar4;
  return;
}



// ========================================================
// Function: __fltout at 0100d61c
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __fltout
   
   Library: Visual Studio 2003 Release */

void __fltout(void)

{
  uint local_14;
  uint uStack_10;
  ushort uStack_c;
  uint local_8;
  
  local_8 = DAT_0101107c;
  ___dtold(&local_14,(uint *)&stack0x00000004);
  _DAT_01013278 = FUN_0100f307(local_14,uStack_10,uStack_c,0x11,0,&DAT_01013254);
  _DAT_01013270 = (int)DAT_01013256;
  _DAT_01013274 = (int)DAT_01013254;
  _DAT_0101327c = &DAT_01013258;
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: _memset at 0100d6a0
// ========================================================

/* Library Function - Single Match
    _memset
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

void * __cdecl _memset(void *_Dst,int _Val,size_t _Size)

{
  uint uVar1;
  uint uVar2;
  size_t sVar3;
  uint *puVar4;
  
  if (_Size == 0) {
    return _Dst;
  }
  uVar1 = _Val & 0xff;
  puVar4 = _Dst;
  if (3 < _Size) {
    uVar2 = -(int)_Dst & 3;
    sVar3 = _Size;
    if (uVar2 != 0) {
      sVar3 = _Size - uVar2;
      do {
        *(undefined1 *)puVar4 = (undefined1)_Val;
        puVar4 = (uint *)((int)puVar4 + 1);
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    uVar1 = uVar1 * 0x1010101;
    _Size = sVar3 & 3;
    uVar2 = sVar3 >> 2;
    if (uVar2 != 0) {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
      }
      if (_Size == 0) {
        return _Dst;
      }
    }
  }
  do {
    *(char *)puVar4 = (char)uVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
    _Size = _Size - 1;
  } while (_Size != 0);
  return _Dst;
}



// ========================================================
// Function: FUN_0100d70b at 0100d70b
// ========================================================

uint __cdecl FUN_0100d70b(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((param_1 & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  uVar2 = param_1 & 0xc00;
  if (uVar2 != 0) {
    if (uVar2 == 0x400) {
      uVar1 = uVar1 | 0x100;
    }
    else if (uVar2 == 0x800) {
      uVar1 = uVar1 | 0x200;
    }
    else if (uVar2 == 0xc00) {
      uVar1 = uVar1 | 0x300;
    }
  }
  if ((param_1 & 0x300) == 0) {
    uVar1 = uVar1 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    uVar1 = uVar1 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    uVar1 = uVar1 | 0x40000;
  }
  return uVar1;
}



// ========================================================
// Function: __hw_cw at 0100d7ac
// ========================================================

/* Library Function - Single Match
    __hw_cw
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

uint __hw_cw(void)

{
  uint uVar1;
  uint uVar2;
  uint unaff_EBX;
  
  uVar1 = (uint)((unaff_EBX & 0x10) != 0);
  if ((unaff_EBX & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((unaff_EBX & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((unaff_EBX & 2) != 0) {
    uVar1 = uVar1 | 0x10;
  }
  if ((unaff_EBX & 1) != 0) {
    uVar1 = uVar1 | 0x20;
  }
  if ((unaff_EBX & 0x80000) != 0) {
    uVar1 = uVar1 | 2;
  }
  uVar2 = unaff_EBX & 0x300;
  if (uVar2 != 0) {
    if (uVar2 == 0x100) {
      uVar1 = uVar1 | 0x400;
    }
    else if (uVar2 == 0x200) {
      uVar1 = uVar1 | 0x800;
    }
    else if (uVar2 == 0x300) {
      uVar1 = uVar1 | 0xc00;
    }
  }
  if ((unaff_EBX & 0x30000) == 0) {
    uVar1 = uVar1 | 0x300;
  }
  else if ((unaff_EBX & 0x30000) == 0x10000) {
    uVar1 = uVar1 | 0x200;
  }
  if ((unaff_EBX & 0x40000) != 0) {
    uVar1 = uVar1 | 0x1000;
  }
  return uVar1;
}



// ========================================================
// Function: FUN_0100d83f at 0100d83f
// ========================================================

uint __thiscall FUN_0100d83f(void *this,uint param_1,uint param_2)

{
  uint uVar1;
  undefined2 in_FPUControlWord;
  undefined4 local_8;
  
  local_8 = CONCAT22((short)((uint)this >> 0x10),in_FPUControlWord);
  uVar1 = FUN_0100d70b(local_8);
  __hw_cw();
  return uVar1 & ~param_2 | param_1 & param_2;
}



// ========================================================
// Function: FUN_0100d879 at 0100d879
// ========================================================

void __thiscall FUN_0100d879(void *this,uint param_1,uint param_2)

{
  FUN_0100d83f(this,param_1,param_2 & 0xfff7ffff);
  return;
}



// ========================================================
// Function: FUN_0100d898 at 0100d898
// ========================================================

undefined4 __cdecl FUN_0100d898(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_01013280 != (code *)0x0) {
    iVar1 = (*DAT_01013280)(param_1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}



// ========================================================
// Function: FUN_0100d8be at 0100d8be
// ========================================================

undefined4 FUN_0100d8be(void)

{
  return 0;
}



// ========================================================
// Function: __raise_exc at 0100d8c6
// ========================================================

/* Library Function - Single Match
    __raise_exc
   
   Library: Visual Studio 2003 Release */

void __cdecl
__raise_exc(uint *param_1,uint *param_2,uint param_3,int param_4,undefined8 *param_5,
           undefined8 *param_6)

{
  uint *puVar1;
  undefined8 *puVar2;
  uint uVar3;
  
  uVar3 = param_3;
  puVar1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  if ((param_3 & 0x10) != 0) {
    param_1[1] = param_1[1] | 1;
    param_3 = 0xc000008f;
  }
  if ((uVar3 & 2) != 0) {
    param_1[1] = param_1[1] | 2;
    param_3 = 0xc0000093;
  }
  if ((uVar3 & 1) != 0) {
    param_1[1] = param_1[1] | 4;
    param_3 = 0xc0000091;
  }
  if ((uVar3 & 4) != 0) {
    param_1[1] = param_1[1] | 8;
    param_3 = 0xc000008e;
  }
  if ((uVar3 & 8) != 0) {
    param_1[1] = param_1[1] | 0x10;
    param_3 = 0xc0000090;
  }
  param_1[2] = param_1[2] ^ (~(*param_2 << 4) ^ param_1[2]) & 0x10;
  param_1[2] = param_1[2] ^ (~(*param_2 << 1) ^ param_1[2]) & 8;
  param_1[2] = param_1[2] ^ (~(*param_2 >> 1) ^ param_1[2]) & 4;
  param_1[2] = param_1[2] ^ (~(*param_2 >> 3) ^ param_1[2]) & 2;
  param_1[2] = param_1[2] ^ (~(*param_2 >> 5) ^ param_1[2]) & 1;
  uVar3 = FUN_0100e13f();
  puVar2 = param_6;
  if ((uVar3 & 1) != 0) {
    param_1[3] = param_1[3] | 0x10;
  }
  if ((uVar3 & 4) != 0) {
    param_1[3] = param_1[3] | 8;
  }
  if ((uVar3 & 8) != 0) {
    param_1[3] = param_1[3] | 4;
  }
  if ((uVar3 & 0x10) != 0) {
    param_1[3] = param_1[3] | 2;
  }
  if ((uVar3 & 0x20) != 0) {
    param_1[3] = param_1[3] | 1;
  }
  uVar3 = *puVar1 & 0xc00;
  if (uVar3 == 0) {
    *param_1 = *param_1 & 0xfffffffc;
  }
  else {
    if (uVar3 == 0x400) {
      uVar3 = *param_1 & 0xfffffffd | 1;
    }
    else {
      if (uVar3 != 0x800) {
        if (uVar3 == 0xc00) {
          *param_1 = *param_1 | 3;
        }
        goto LAB_0100da25;
      }
      uVar3 = *param_1 & 0xfffffffe | 2;
    }
    *param_1 = uVar3;
  }
LAB_0100da25:
  uVar3 = *puVar1 & 0x300;
  if (uVar3 == 0) {
    uVar3 = *param_1 & 0xffffffeb | 8;
LAB_0100da5b:
    *param_1 = uVar3;
  }
  else {
    if (uVar3 == 0x200) {
      uVar3 = *param_1 & 0xffffffe7 | 4;
      goto LAB_0100da5b;
    }
    if (uVar3 == 0x300) {
      *param_1 = *param_1 & 0xffffffe3;
    }
  }
  *param_1 = *param_1 ^ (param_4 << 5 ^ *param_1) & 0x1ffe0;
  param_1[8] = param_1[8] | 1;
  param_1[8] = param_1[8] & 0xffffffe3 | 2;
  *(undefined8 *)(param_1 + 4) = *param_5;
  param_1[0x18] = param_1[0x18] | 1;
  param_1[0x18] = param_1[0x18] & 0xffffffe3 | 2;
  *(undefined8 *)(param_1 + 0x14) = *param_6;
  FUN_0100e154();
  RaiseException(param_3,0,1,(ULONG_PTR *)&param_1);
  if ((param_1[2] & 0x10) != 0) {
    *puVar1 = *puVar1 & 0xfffffffe;
  }
  if ((param_1[2] & 8) != 0) {
    *puVar1 = *puVar1 & 0xfffffffb;
  }
  if ((param_1[2] & 4) != 0) {
    *puVar1 = *puVar1 & 0xfffffff7;
  }
  if ((param_1[2] & 2) != 0) {
    *puVar1 = *puVar1 & 0xffffffef;
  }
  if ((param_1[2] & 1) != 0) {
    *puVar1 = *puVar1 & 0xffffffdf;
  }
  uVar3 = *param_1 & 3;
  if (uVar3 == 0) {
    *puVar1 = *puVar1 & 0xfffff3ff;
  }
  else {
    if (uVar3 == 1) {
      uVar3 = *puVar1 & 0xfffff7ff | 0x400;
    }
    else {
      if (uVar3 != 2) {
        if (uVar3 == 3) {
          *(byte *)((int)puVar1 + 1) = *(byte *)((int)puVar1 + 1) | 0xc;
        }
        goto LAB_0100db34;
      }
      uVar3 = *puVar1 & 0xfffffbff | 0x800;
    }
    *puVar1 = uVar3;
  }
LAB_0100db34:
  uVar3 = *param_1 >> 2 & 7;
  if (uVar3 == 0) {
    uVar3 = *puVar1 & 0xfffff3ff | 0x300;
  }
  else {
    if (uVar3 != 1) {
      if (uVar3 == 2) {
        *puVar1 = *puVar1 & 0xfffff3ff;
      }
      goto LAB_0100db63;
    }
    uVar3 = *puVar1 & 0xfffff3ff | 0x200;
  }
  *puVar1 = uVar3;
LAB_0100db63:
  *puVar2 = *(undefined8 *)(param_1 + 0x14);
  return;
}



// ========================================================
// Function: __handle_exc at 0100db72
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __handle_exc
   
   Library: Visual Studio 2003 Release */

bool __cdecl __handle_exc(uint param_1,double *param_2,uint param_3)

{
  double dVar1;
  bool bVar2;
  uint uVar3;
  bool bVar4;
  float10 fVar5;
  undefined8 local_14;
  int local_c;
  uint local_8;
  
  uVar3 = param_1 & 0x1f;
  bVar2 = true;
  local_8 = uVar3;
  if (((param_1 & 8) != 0) && ((param_3 & 1) != 0)) {
    FUN_0100e195();
    uVar3 = param_1 & 0x17;
    goto LAB_0100dd76;
  }
  if (((param_1 & 4) != 0) && ((param_3 & 4) != 0)) {
    FUN_0100e195();
    uVar3 = param_1 & 0x1b;
    goto LAB_0100dd76;
  }
  if (((param_1 & 1) == 0) || ((param_3 & 8) == 0)) {
    if (((param_1 & 2) != 0) && ((param_3 & 0x10) != 0)) {
      bVar4 = (param_1 & 0x10) != 0;
      if (*param_2 != _DAT_01001a38) {
        fVar5 = __decomp(SUB84(*param_2,0),(uint)((ulonglong)*param_2 >> 0x20),&local_c);
        dVar1 = (double)fVar5;
        local_c = local_c + -0x600;
        if (local_c < -0x432) {
          local_14 = dVar1 * _DAT_01001a38;
          bVar4 = bVar2;
        }
        else {
          local_14 = (double)((ulonglong)dVar1 & 0xfffffffffffff | 0x10000000000000);
          if (local_c < -0x3fd) {
            local_c = -0x3fd - local_c;
            do {
              if ((((ulonglong)local_14 & 1) != 0) && (!bVar4)) {
                bVar4 = bVar2;
              }
              uVar3 = (uint)local_14 >> 1;
              if (((ulonglong)local_14 & 0x100000000) != 0) {
                local_14._3_1_ = (byte)((ulonglong)local_14 >> 0x18) >> 1;
                local_14._0_3_ = (undefined3)uVar3;
                local_14._0_4_ = CONCAT13(local_14._3_1_,(undefined3)local_14) | 0x80000000;
                uVar3 = (uint)local_14;
              }
              local_14._0_4_ = uVar3;
              local_14 = (double)CONCAT44(local_14._4_4_ >> 1,(uint)local_14);
              local_c = local_c + -1;
            } while (local_c != 0);
          }
          if (dVar1 < _DAT_01001a38) {
            local_14 = -local_14;
          }
        }
        *param_2 = local_14;
        bVar2 = bVar4;
      }
      if (bVar2) {
        FUN_0100e195();
      }
      uVar3 = local_8 & 0xfffffffd;
      local_8 = uVar3;
    }
    goto LAB_0100dd76;
  }
  FUN_0100e195();
  uVar3 = param_3 & 0xc00;
  dVar1 = _DAT_010114c0;
  if (uVar3 == 0) {
    if (*param_2 <= _DAT_01001a38) {
      dVar1 = -_DAT_010114c0;
    }
LAB_0100dc92:
    *param_2 = dVar1;
  }
  else {
    if (uVar3 == 0x400) {
      dVar1 = _DAT_010114d0;
      if (*param_2 <= _DAT_01001a38) {
        dVar1 = -_DAT_010114c0;
      }
      goto LAB_0100dc92;
    }
    if (uVar3 == 0x800) {
      if (*param_2 <= _DAT_01001a38) {
        dVar1 = -_DAT_010114d0;
      }
      goto LAB_0100dc92;
    }
    if (uVar3 == 0xc00) {
      dVar1 = _DAT_010114d0;
      if (*param_2 <= _DAT_01001a38) {
        dVar1 = -_DAT_010114d0;
      }
      goto LAB_0100dc92;
    }
  }
  uVar3 = param_1 & 0x1e;
LAB_0100dd76:
  if (((param_1 & 0x10) != 0) && ((param_3 & 0x20) != 0)) {
    FUN_0100e195();
    uVar3 = uVar3 & 0xffffffef;
  }
  return uVar3 == 0;
}



// ========================================================
// Function: __set_errno_from_matherr at 0100dd9d
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __set_errno_from_matherr
   
   Library: Visual Studio 2019 Release */

void __cdecl __set_errno_from_matherr(int param_1)

{
  if (param_1 == 1) {
    _DAT_01013060 = 0x21;
  }
  else if ((1 < param_1) && (param_1 < 4)) {
    _DAT_01013060 = 0x22;
    return;
  }
  return;
}



// ========================================================
// Function: FUN_0100ddcd at 0100ddcd
// ========================================================

int __cdecl FUN_0100ddcd(byte param_1)

{
  undefined4 uStack_8;
  
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 8) != 0) {
      return 1;
    }
    if ((param_1 & 4) == 0) {
      if ((param_1 & 1) == 0) {
        return (param_1 & 2) << 1;
      }
      uStack_8 = 3;
    }
    else {
      uStack_8 = 2;
    }
  }
  else {
    uStack_8 = 5;
  }
  return uStack_8;
}



// ========================================================
// Function: __umatherr at 0100de06
// ========================================================

/* Library Function - Single Match
    __umatherr
   
   Library: Visual Studio 2003 Release */

float10 __cdecl __umatherr(int param_1,int param_2)

{
  int iVar1;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000020;
  
  iVar1 = 0;
  do {
    if ((&DAT_010113d8)[iVar1 * 2] == param_2) {
      iVar1 = *(int *)(iVar1 * 8 + 0x10113dc);
      goto LAB_0100de24;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1d);
  iVar1 = 0;
LAB_0100de24:
  if (iVar1 != 0) {
    __ctrlfp();
    iVar1 = FUN_0100d8be();
    if (iVar1 == 0) {
      __set_errno_from_matherr(param_1);
    }
    return (float10)(double)CONCAT44(in_stack_00000020,in_stack_0000001c);
  }
  __ctrlfp();
  __set_errno_from_matherr(param_1);
  return (float10)(double)CONCAT44(in_stack_00000020,in_stack_0000001c);
}



// ========================================================
// Function: __handle_qnan1 at 0100dead
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __handle_qnan1
   
   Library: Visual Studio 2003 Release */

float10 __cdecl __handle_qnan1(int param_1,double param_2)

{
  float10 fVar1;
  
  if (DAT_010113d0 == 0) {
    fVar1 = __umatherr(1,param_1);
    return fVar1;
  }
  _DAT_01013060 = 0x21;
  __ctrlfp();
  return (float10)param_2;
}



// ========================================================
// Function: FUN_0100df06 at 0100df06
// ========================================================

void __cdecl FUN_0100df06(uint param_1,int param_2,undefined8 param_3,double param_4,uint param_5)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint local_90 [16];
  uint local_50;
  uint local_14;
  
  local_14 = DAT_0101107c;
  bVar1 = __handle_exc(param_1,&param_4,param_5);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    local_50 = local_50 & 0xfffffffe;
    __raise_exc(local_90,&param_5,param_1,param_2,&param_3,&param_4);
  }
  iVar2 = FUN_0100ddcd((byte)param_1);
  if ((DAT_010113d0 == 0) && (iVar2 != 0)) {
    __umatherr(iVar2,param_2);
  }
  else {
    __set_errno_from_matherr(iVar2);
    __ctrlfp();
  }
  FUN_01008e6b(local_14);
  return;
}



// ========================================================
// Function: __frnd at 0100dfd0
// ========================================================

/* Library Function - Single Match
    __frnd
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release,
   Visual Studio 2019 Release */

float10 __cdecl __frnd(double param_1)

{
  return (float10)ROUND(param_1);
}



// ========================================================
// Function: __set_exp at 0100dfe9
// ========================================================

/* Library Function - Single Match
    __set_exp
   
   Library: Visual Studio 2003 Release */

float10 __cdecl __set_exp(undefined8 param_1,short param_2)

{
  undefined8 local_c;
  
  local_c = (double)CONCAT26((param_2 + 0x3fe) * 0x10 | param_1._6_2_ & 0x800f,(int6)param_1);
  return (float10)local_c;
}



// ========================================================
// Function: __sptype at 0100e01a
// ========================================================

/* Library Function - Single Match
    __sptype
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl __sptype(int param_1,uint param_2)

{
  undefined4 uStack_8;
  
  if (param_2 == 0x7ff00000) {
    if (param_1 == 0) {
      return 1;
    }
  }
  else if ((param_2 == 0xfff00000) && (param_1 == 0)) {
    return 2;
  }
  if ((param_2._2_2_ & 0x7ff8) == 0x7ff8) {
    uStack_8 = 3;
  }
  else {
    if (((param_2._2_2_ & 0x7ff8) != 0x7ff0) || (((param_2 & 0x7ffff) == 0 && (param_1 == 0)))) {
      return 0;
    }
    uStack_8 = 4;
  }
  return uStack_8;
}



// ========================================================
// Function: __decomp at 0100e07c
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __decomp
   
   Library: Visual Studio 2003 Release */

float10 __cdecl __decomp(uint param_1,uint param_2,int *param_3)

{
  bool bVar1;
  int iVar2;
  int extraout_EDX;
  float10 fVar3;
  
  if ((double)CONCAT17(param_2._3_1_,CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))) ==
      _DAT_01001a38) {
    fVar3 = (float10)0;
    iVar2 = 0;
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    if (_DAT_01001a38 <=
        (double)CONCAT17(param_2._3_1_,CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1)))) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    while ((param_2._2_1_ & 0x10) == 0) {
      iVar2 = CONCAT13(param_2._3_1_,CONCAT12(param_2._2_1_,(ushort)param_2)) << 1;
      param_2._0_2_ = (ushort)iVar2;
      param_2._2_1_ = (byte)((uint)iVar2 >> 0x10);
      param_2._3_1_ = (byte)((uint)iVar2 >> 0x18);
      if ((param_1 & 0x80000000) != 0) {
        param_2._0_2_ = (ushort)param_2 | 1;
      }
      param_1 = param_1 << 1;
    }
    if (bVar1) {
      param_2._3_1_ = param_2._3_1_ | 0x80;
    }
    fVar3 = __set_exp(CONCAT17(param_2._3_1_,
                               CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))) &
                      0xffefffffffffffff,0);
    iVar2 = extraout_EDX;
  }
  else {
    fVar3 = __set_exp(CONCAT17(param_2._3_1_,
                               CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))),0);
    iVar2 = ((param_2 >> 0x10 & 0x7ff0) >> 4) - 0x3fe;
  }
  *param_3 = iVar2;
  return (float10)(double)fVar3;
}



// ========================================================
// Function: FUN_0100e13f at 0100e13f
// ========================================================

int FUN_0100e13f(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}



// ========================================================
// Function: FUN_0100e154 at 0100e154
// ========================================================

int FUN_0100e154(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}



// ========================================================
// Function: __ctrlfp at 0100e16a
// ========================================================

/* Library Function - Single Match
    __ctrlfp
   
   Library: Visual Studio 2003 Release */

int __ctrlfp(void)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}



// ========================================================
// Function: FUN_0100e195 at 0100e195
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0100e195(void)

{
  return;
}



// ========================================================
// Function: __trandisp1 at 0100e200
// ========================================================

/* Library Function - Single Match
    __trandisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __fastcall __trandisp1(undefined4 param_1,int param_2)

{
  float10 fVar1;
  byte bVar2;
  undefined2 uVar3;
  int unaff_EBP;
  float10 in_ST0;
  
  if (*(char *)(param_2 + 0xe) == '\x05') {
    uVar3 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar3 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar3;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = param_2;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  bVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    /* WARNING: Could not recover jumptable at 0x0100e265. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_2 + (char)(&DAT_0101151d)[(byte)((bVar2 & 7) << 1 | (char)bVar2 < '\0')] + 0x10
              ))();
  return;
}



// ========================================================
// Function: __trandisp2 at 0100e267
// ========================================================

/* Library Function - Single Match
    __trandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __fastcall __trandisp2(undefined4 param_1,int param_2)

{
  float10 fVar1;
  char cVar2;
  byte bVar3;
  undefined2 uVar4;
  int unaff_EBP;
  float10 in_ST0;
  float10 in_ST1;
  
  if (*(char *)(param_2 + 0xe) == '\x05') {
    uVar4 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar4 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar4;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = param_2;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  fVar1 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST1) << 8 | (ushort)(in_ST1 < fVar1) << 9 | (ushort)(in_ST1 != fVar1) << 10 |
       (ushort)(in_ST1 == fVar1) << 0xe;
  bVar3 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
  cVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    /* WARNING: Could not recover jumptable at 0x0100e2f1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_2 + (char)((&DAT_0101151d)[(byte)(cVar2 << 1 | cVar2 < '\0') & 0xf] |
                               (&DAT_0101151d)[(byte)((bVar3 & 7) << 1 | (char)bVar3 < '\0')] << 2)
              + 0x10))();
  return;
}



// ========================================================
// Function: FUN_0100e2f8 at 0100e2f8
// ========================================================

void FUN_0100e2f8(void)

{
  return;
}



// ========================================================
// Function: FUN_0100e306 at 0100e306
// ========================================================

float10 FUN_0100e306(void)

{
  return (float10)0;
}



// ========================================================
// Function: __d_inttype at 0100e3cf
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __d_inttype
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl __d_inttype(double param_1)

{
  double dVar1;
  uint uVar2;
  float10 fVar3;
  
  uVar2 = __fpclass(param_1);
  if ((uVar2 & 0x90) == 0) {
    fVar3 = __frnd(param_1);
    if ((double)fVar3 == param_1) {
      dVar1 = param_1 / _DAT_01002560;
      fVar3 = __frnd(dVar1);
      if ((float10)dVar1 == fVar3) {
        return 2;
      }
      return 1;
    }
  }
  return 0;
}



// ========================================================
// Function: __powhlp at 0100e444
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __powhlp
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl __powhlp(int param_1,int param_2,double param_3,double *param_4)

{
  double dVar1;
  double dVar2;
  int iVar3;
  undefined4 uVar4;
  
  dVar1 = (double)CONCAT44(param_2,param_1);
  uVar4 = 0;
  if (dVar1 < _DAT_01001a38) {
    dVar1 = -dVar1;
  }
  dVar2 = _DAT_010114c0;
  if (param_3._4_4_ == 0x7ff00000) {
    if (param_3._0_4_ != 0) goto LAB_0100e4f1;
    if (_DAT_01001b10 < dVar1) goto LAB_0100e5a1;
    if (_DAT_01001b10 <= dVar1) goto LAB_0100e4a4;
  }
  else {
    if (param_3 == -INFINITY) {
      if (_DAT_01001b10 < dVar1) {
        dVar2 = 0.0;
        goto LAB_0100e5a1;
      }
      if (dVar1 < _DAT_01001b10) goto LAB_0100e5a1;
LAB_0100e4a4:
      uVar4 = 1;
      dVar2 = _DAT_010114c8;
      goto LAB_0100e5a1;
    }
LAB_0100e4f1:
    if (param_2 != 0x7ff00000) {
      if (param_2 != -0x100000) {
        return 0;
      }
      if (param_1 != 0) {
        return 0;
      }
      iVar3 = __d_inttype(param_3);
      if (param_3 <= _DAT_01001a38) {
        if (_DAT_01001a38 <= param_3) {
          dVar2 = 1.0;
        }
        else {
          dVar2 = _DAT_010114e0;
          if (iVar3 != 1) {
            dVar2 = 0.0;
          }
        }
      }
      else {
        dVar2 = _DAT_010114c0;
        if (iVar3 == 1) {
          dVar2 = -_DAT_010114c0;
        }
      }
      goto LAB_0100e5a1;
    }
    if (param_1 != 0) {
      return 0;
    }
    if (_DAT_01001a38 < param_3) goto LAB_0100e5a1;
    if (_DAT_01001a38 <= param_3) {
      dVar2 = 1.0;
      goto LAB_0100e5a1;
    }
  }
  dVar2 = 0.0;
LAB_0100e5a1:
  *param_4 = dVar2;
  return uVar4;
}



// ========================================================
// Function: FUN_0100e5ad at 0100e5ad
// ========================================================

void __cdecl FUN_0100e5ad(int param_1,int *param_2,ushort *param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint local_98;
  uint local_94;
  uint local_90 [12];
  undefined8 local_60;
  uint local_50;
  uint local_14;
  
  local_14 = DAT_0101107c;
  local_98 = (uint)*param_3;
  iVar2 = *param_2;
  if (iVar2 == 1) {
LAB_0100e63a:
    local_94 = 8;
LAB_0100e644:
    bVar1 = __handle_exc(local_94,(double *)(param_2 + 6),local_98);
    if (CONCAT31(extraout_var,bVar1) == 0) {
      if (((param_1 == 0x10) || (param_1 == 0x16)) || (param_1 == 0x1d)) {
        local_60 = *(undefined8 *)(param_2 + 4);
        local_50 = local_50 & 0xffffffe3 | 3;
      }
      else {
        local_50 = local_50 & 0xfffffffe;
      }
      __raise_exc(local_90,&local_98,local_94,param_1,(undefined8 *)(param_2 + 2),
                  (undefined8 *)(param_2 + 6));
    }
  }
  else {
    if (iVar2 == 2) {
      local_94 = 4;
      goto LAB_0100e644;
    }
    if (iVar2 == 3) {
      local_94 = 0x11;
      goto LAB_0100e644;
    }
    if (iVar2 == 4) {
      local_94 = 0x12;
      goto LAB_0100e644;
    }
    if (iVar2 == 5) goto LAB_0100e63a;
    if (iVar2 == 7) {
      *param_2 = 1;
    }
    else if (iVar2 == 8) {
      local_94 = 0x10;
      goto LAB_0100e644;
    }
  }
  __ctrlfp();
  if ((*param_2 != 8) && (DAT_010113d0 == 0)) {
    iVar2 = FUN_0100d8be();
    if (iVar2 != 0) goto LAB_0100e6d7;
  }
  __set_errno_from_matherr(*param_2);
LAB_0100e6d7:
  FUN_01008e6b(local_14);
  return;
}



// ========================================================
// Function: FUN_0100e6ed at 0100e6ed
// ========================================================

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Unable to track spacebase fully for stack */

uint __cdecl
FUN_0100e6ed(LCID param_1,uint param_2,LPCSTR param_3,int param_4,LPSTR param_5,int param_6,
            UINT param_7,int param_8)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  DWORD DVar4;
  char *pcVar5;
  undefined1 *puVar6;
  int iVar7;
  UINT UVar8;
  uint *puVar9;
  LPCSTR lpDestStr;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  undefined1 *puVar13;
  uint uVar14;
  undefined4 *puVar15;
  LPCSTR pCVar16;
  undefined4 uStackY_70;
  LPCSTR local_2c;
  uint *local_28;
  undefined1 *local_24;
  undefined1 *local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_01002570;
  uStack_c = 0x100e6f9;
  uVar14 = 0;
  if (DAT_010132a8 == 0) {
    uStackY_70 = 0x100e71a;
    iVar3 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
    if (iVar3 == 0) {
      DVar4 = GetLastError();
      if (DVar4 == 0x78) {
        DAT_010132a8 = 2;
      }
    }
    else {
      DAT_010132a8 = 1;
    }
  }
  pcVar5 = param_3;
  iVar3 = param_4;
  if (0 < param_4) {
    do {
      iVar3 = iVar3 + -1;
      if (*pcVar5 == '\0') goto LAB_0100e754;
      pcVar5 = pcVar5 + 1;
    } while (iVar3 != 0);
    iVar3 = -1;
LAB_0100e754:
    param_4 = param_4 + (-1 - iVar3);
  }
  if ((DAT_010132a8 != 2) && (DAT_010132a8 != 0)) {
    if (DAT_010132a8 == 1) {
      bVar2 = false;
      bVar1 = false;
      if (param_7 == 0) {
        param_7 = DAT_010132a0;
      }
      uStackY_70 = 0x100e7b2;
      iVar3 = MultiByteToWideChar(param_7,(uint)(param_8 != 0) * 8 + 1,param_3,param_4,(LPWSTR)0x0,0
                                 );
      if (iVar3 != 0) {
        puVar6 = (undefined1 *)(iVar3 * 2 + 3U & 0xfffffffc);
        iVar7 = -(int)puVar6;
        local_1c = &stack0xffffffac + iVar7;
        local_20 = &stack0xffffffac + iVar7;
        local_8 = (undefined *)0xffffffff;
        if (&stack0xffffffac == puVar6) {
          *(int *)(&stack0xffffffa8 + iVar7) = iVar3 * 2;
          *(undefined4 *)(&stack0xffffffa4 + iVar7) = 0x100e80e;
          local_20 = (undefined1 *)FUN_0100a80d(*(uint **)(&stack0xffffffa8 + iVar7));
          if (local_20 == (undefined1 *)0x0) {
            return 0;
          }
          bVar2 = true;
        }
        *(int *)(&stack0xffffffa8 + iVar7) = iVar3;
        *(undefined1 **)(&stack0xffffffa4 + iVar7) = local_20;
        *(int *)(&stack0xffffffa0 + iVar7) = param_4;
        *(LPCSTR *)(&stack0xffffff9c + iVar7) = param_3;
        *(undefined4 *)(&stack0xffffff98 + iVar7) = 1;
        *(UINT *)(&stack0xffffff94 + iVar7) = param_7;
        puVar10 = (undefined1 *)((int)&uStackY_70 + iVar7);
        *(undefined4 *)((int)&uStackY_70 + iVar7) = 0x100e836;
        iVar7 = MultiByteToWideChar(*(UINT *)(&stack0xffffff94 + iVar7),
                                    *(DWORD *)(&stack0xffffff98 + iVar7),
                                    *(LPCSTR *)(&stack0xffffff9c + iVar7),
                                    *(int *)(&stack0xffffffa0 + iVar7),
                                    *(LPWSTR *)(&stack0xffffffa4 + iVar7),
                                    *(int *)(&stack0xffffffa8 + iVar7));
        puVar6 = puVar10;
        if (iVar7 != 0) {
          *(undefined4 *)(puVar10 + -4) = 0;
          *(undefined4 *)(puVar10 + -8) = 0;
          *(int *)(puVar10 + -0xc) = iVar3;
          *(undefined1 **)(puVar10 + -0x10) = local_20;
          *(uint *)(puVar10 + -0x14) = param_2;
          *(LCID *)(puVar10 + -0x18) = param_1;
          puVar11 = puVar10 + -0x1c;
          *(undefined4 *)(puVar10 + -0x1c) = 0x100e850;
          uVar14 = LCMapStringW(*(LCID *)(puVar10 + -0x18),*(DWORD *)(puVar10 + -0x14),
                                *(LPCWSTR *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc),
                                *(LPWSTR *)(puVar10 + -8),*(int *)(puVar10 + -4));
          puVar6 = puVar11;
          if (uVar14 != 0) {
            if ((param_2 & 0x400) == 0) {
              puVar6 = (undefined1 *)(uVar14 * 2 + 3 & 0xfffffffc);
              *(undefined4 *)(puVar11 + -4) = 0x100e8a5;
              iVar7 = -(int)puVar6;
              local_1c = puVar11 + iVar7;
              local_24 = puVar11 + iVar7;
              local_8 = (undefined *)0xffffffff;
              if (puVar11 == puVar6) {
                *(uint *)(puVar11 + iVar7 + -4) = uVar14 * 2;
                *(undefined4 *)(puVar11 + iVar7 + -8) = 0x100e8dd;
                local_24 = (undefined1 *)FUN_0100a80d(*(uint **)(puVar11 + iVar7 + -4));
                puVar6 = puVar11 + iVar7;
                if (local_24 == (undefined1 *)0x0) goto LAB_0100e925;
                bVar1 = true;
              }
              *(uint *)(puVar11 + iVar7 + -4) = uVar14;
              *(undefined1 **)(puVar11 + iVar7 + -8) = local_24;
              *(int *)(puVar11 + iVar7 + -0xc) = iVar3;
              *(undefined1 **)(puVar11 + iVar7 + -0x10) = local_20;
              *(uint *)(puVar11 + iVar7 + -0x14) = param_2;
              *(LCID *)(puVar11 + iVar7 + -0x18) = param_1;
              puVar13 = puVar11 + iVar7 + -0x1c;
              *(undefined4 *)(puVar11 + iVar7 + -0x1c) = 0x100e900;
              iVar3 = LCMapStringW(*(LCID *)(puVar11 + iVar7 + -0x18),
                                   *(DWORD *)(puVar11 + iVar7 + -0x14),
                                   *(LPCWSTR *)(puVar11 + iVar7 + -0x10),
                                   *(int *)(puVar11 + iVar7 + -0xc),
                                   *(LPWSTR *)(puVar11 + iVar7 + -8),*(int *)(puVar11 + iVar7 + -4))
              ;
              puVar6 = puVar13;
              if (iVar3 != 0) {
                *(undefined4 *)(puVar13 + -4) = 0;
                *(undefined4 *)(puVar13 + -8) = 0;
                if (param_6 == 0) {
                  *(undefined4 *)(puVar13 + -0xc) = 0;
                  *(undefined4 *)(puVar13 + -0x10) = 0;
                }
                else {
                  *(int *)(puVar13 + -0xc) = param_6;
                  *(LPSTR *)(puVar13 + -0x10) = param_5;
                }
                *(uint *)(puVar13 + -0x14) = uVar14;
                *(undefined1 **)(puVar13 + -0x18) = local_24;
                *(undefined4 *)(puVar13 + -0x1c) = 0;
                *(UINT *)(puVar13 + -0x20) = param_7;
                puVar6 = puVar13 + -0x24;
                *(undefined4 *)(puVar13 + -0x24) = 0x100e923;
                uVar14 = WideCharToMultiByte(*(UINT *)(puVar13 + -0x20),*(DWORD *)(puVar13 + -0x1c),
                                             *(LPCWSTR *)(puVar13 + -0x18),*(int *)(puVar13 + -0x14)
                                             ,*(LPSTR *)(puVar13 + -0x10),*(int *)(puVar13 + -0xc),
                                             *(LPCSTR *)(puVar13 + -8),*(LPBOOL *)(puVar13 + -4));
              }
            }
            else if ((param_6 != 0) && ((int)uVar14 <= param_6)) {
              *(int *)(puVar11 + -4) = param_6;
              *(LPSTR *)(puVar11 + -8) = param_5;
              *(int *)(puVar11 + -0xc) = iVar3;
              *(undefined1 **)(puVar11 + -0x10) = local_20;
              *(uint *)(puVar11 + -0x14) = param_2;
              *(LCID *)(puVar11 + -0x18) = param_1;
              puVar12 = puVar11 + -0x1c;
              *(undefined4 *)(puVar11 + -0x1c) = 0x100e88b;
              LCMapStringW(*(LCID *)(puVar11 + -0x18),*(DWORD *)(puVar11 + -0x14),
                           *(LPCWSTR *)(puVar11 + -0x10),*(int *)(puVar11 + -0xc),
                           *(LPWSTR *)(puVar11 + -8),*(int *)(puVar11 + -4));
              puVar6 = puVar12;
            }
          }
        }
LAB_0100e925:
        if (bVar1) {
          *(undefined1 **)(puVar6 + -4) = local_24;
          *(undefined4 *)(puVar6 + -8) = 0x100e932;
          FUN_0100a312(*(LPVOID *)(puVar6 + -4));
        }
        if (bVar2) {
          *(undefined1 **)(puVar6 + -4) = local_20;
          *(undefined4 *)(puVar6 + -8) = 0x100e940;
          FUN_0100a312(*(LPVOID *)(puVar6 + -4));
          return uVar14;
        }
        return uVar14;
      }
    }
    return 0;
  }
  local_2c = (LPCSTR)0x0;
  lpDestStr = (LPCSTR)0x0;
  bVar1 = false;
  if (param_1 == 0) {
    param_1 = DAT_01013290;
  }
  if (param_7 == 0) {
    param_7 = DAT_010132a0;
  }
  UVar8 = ___ansicp(param_1);
  if (UVar8 == 0xffffffff) {
    return 0;
  }
  if (UVar8 == param_7) {
    uStackY_70 = 0x100ea9d;
    uVar14 = LCMapStringA(param_1,param_2,param_3,param_4,param_5,param_6);
    goto LAB_0100ea9f;
  }
  uStackY_70 = 0x100e99d;
  local_2c = (LPCSTR)FUN_0100f693(param_7,UVar8,param_3,&param_4,(LPSTR)0x0,0);
  if (local_2c == (LPCSTR)0x0) {
    return 0;
  }
  uStackY_70 = 0x100e9b9;
  puVar9 = (uint *)LCMapStringA(param_1,param_2,local_2c,param_4,(LPSTR)0x0,0);
  local_28 = puVar9;
  if (puVar9 == (uint *)0x0) {
LAB_0100ea51:
    uVar14 = 0;
  }
  else {
    local_1c = &stack0xffffffac;
    lpDestStr = &stack0xffffffac;
    puVar15 = (undefined4 *)&stack0xffffffac;
    for (uVar14 = (uint)puVar9 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
      *puVar15 = 0;
      puVar15 = puVar15 + 1;
    }
    for (uVar14 = (uint)puVar9 & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
      *(undefined1 *)puVar15 = 0;
      puVar15 = (undefined4 *)((int)puVar15 + 1);
    }
    local_8 = (undefined *)0xffffffff;
    if (&stack0x00000000 == (undefined1 *)0x54) {
      lpDestStr = (LPCSTR)FUN_0100a80d(local_28);
      if (lpDestStr == (LPCSTR)0x0) goto LAB_0100ea51;
      pCVar16 = lpDestStr;
      for (uVar14 = (uint)local_28 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
        pCVar16[0] = '\0';
        pCVar16[1] = '\0';
        pCVar16[2] = '\0';
        pCVar16[3] = '\0';
        pCVar16 = pCVar16 + 4;
      }
      for (uVar14 = (uint)local_28 & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
        *pCVar16 = '\0';
        pCVar16 = pCVar16 + 1;
      }
      bVar1 = true;
    }
    uStackY_70 = 0x100ea4a;
    local_28 = (uint *)LCMapStringA(param_1,param_2,local_2c,param_4,lpDestStr,(int)local_28);
    if (local_28 == (uint *)0x0) goto LAB_0100ea51;
    uStackY_70 = 0x100ea6b;
    iVar3 = FUN_0100f693(UVar8,param_7,lpDestStr,(int *)&local_28,param_5,param_6);
    uVar14 = (uint)(iVar3 != 0);
  }
  if (bVar1) {
    FUN_0100a312(lpDestStr);
  }
LAB_0100ea9f:
  if (local_2c != (LPCSTR)0x0) {
    FUN_0100a312(local_2c);
    return uVar14;
  }
  return uVar14;
}



// ========================================================
// Function: FUN_0100eabe at 0100eabe
// ========================================================

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Unable to track spacebase fully for stack */

BOOL __cdecl
FUN_0100eabe(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6,
            int param_7)

{
  bool bVar1;
  BOOL BVar2;
  DWORD DVar3;
  uint uVar4;
  undefined1 *puVar5;
  int *piVar6;
  int iVar7;
  UINT UVar8;
  uint uVar9;
  UINT UVar10;
  undefined1 *puVar11;
  LPCSTR pCVar12;
  undefined4 *puVar13;
  LCID Locale;
  undefined4 uStackY_58;
  BOOL local_28;
  WORD local_20 [2];
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_01002598;
  uStack_c = 0x100eaca;
  pCVar12 = (LPCSTR)0x0;
  if (DAT_010132ac == 0) {
    BVar2 = GetStringTypeW(1,L"",1,local_20);
    if (BVar2 == 0) {
      DVar3 = GetLastError();
      if (DVar3 == 0x78) {
        DAT_010132ac = 2;
      }
    }
    else {
      DAT_010132ac = 1;
    }
  }
  if ((DAT_010132ac == 2) || (DAT_010132ac == 0)) {
    Locale = param_6;
    if (param_6 == 0) {
      Locale = DAT_01013290;
    }
    UVar10 = param_5;
    if (param_5 == 0) {
      UVar10 = DAT_010132a0;
    }
    UVar8 = ___ansicp(Locale);
    if (UVar8 != 0xffffffff) {
      if (UVar8 != UVar10) {
        uStackY_58 = 0x100ec49;
        pCVar12 = (LPCSTR)FUN_0100f693(UVar10,UVar8,param_2,&param_3,(LPSTR)0x0,0);
        param_2 = pCVar12;
        if (pCVar12 == (LPCSTR)0x0) {
          return 0;
        }
      }
      BVar2 = GetStringTypeA(Locale,param_1,param_2,param_3,param_4);
      if (pCVar12 != (LPCSTR)0x0) {
        FUN_0100a312(pCVar12);
        return BVar2;
      }
      return BVar2;
    }
  }
  else if (DAT_010132ac == 1) {
    local_28 = 0;
    bVar1 = false;
    if (param_5 == 0) {
      param_5 = DAT_010132a0;
    }
    uStackY_58 = 0x100eb5c;
    uVar4 = MultiByteToWideChar(param_5,(uint)(param_7 != 0) * 8 + 1,param_2,param_3,(LPWSTR)0x0,0);
    if (uVar4 != 0) {
      puVar5 = (undefined1 *)(uVar4 * 2 + 3 & 0xfffffffc);
      iVar7 = -(int)puVar5;
      piVar6 = (int *)(&stack0xffffffc4 + iVar7);
      local_1c = &stack0xffffffc4 + iVar7;
      puVar13 = (undefined4 *)(&stack0xffffffc4 + iVar7);
      for (uVar9 = (uVar4 & 0x7fffffff) >> 1; uVar9 != 0; uVar9 = uVar9 - 1) {
        *puVar13 = 0;
        puVar13 = puVar13 + 1;
      }
      for (uVar9 = uVar4 * 2 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined1 *)puVar13 = 0;
        puVar13 = (undefined4 *)((int)puVar13 + 1);
      }
      local_8 = (undefined *)0xffffffff;
      if (&stack0xffffffc4 == puVar5) {
        *(uint *)((int)local_20 + iVar7 + -0x20) = uVar4;
        *(undefined4 *)(&stack0xffffffbc + iVar7) = 2;
        *(undefined4 *)(&stack0xffffffb8 + iVar7) = 0x100ebc0;
        piVar6 = FUN_0100f906(*(uint *)(&stack0xffffffbc + iVar7),
                              *(uint *)((int)local_20 + iVar7 + -0x20));
        if (piVar6 == (int *)0x0) {
          return 0;
        }
        bVar1 = true;
      }
      *(uint *)((int)local_20 + iVar7 + -0x20) = uVar4;
      *(int **)(&stack0xffffffbc + iVar7) = piVar6;
      *(int *)(&stack0xffffffb8 + iVar7) = param_3;
      *(LPCSTR *)(&stack0xffffffb4 + iVar7) = param_2;
      *(undefined4 *)(&stack0xffffffb0 + iVar7) = 1;
      *(UINT *)(&stack0xffffffac + iVar7) = param_5;
      puVar11 = (undefined1 *)((int)&uStackY_58 + iVar7);
      *(undefined4 *)((int)&uStackY_58 + iVar7) = 0x100ebe2;
      iVar7 = MultiByteToWideChar(*(UINT *)(&stack0xffffffac + iVar7),
                                  *(DWORD *)(&stack0xffffffb0 + iVar7),
                                  *(LPCSTR *)(&stack0xffffffb4 + iVar7),
                                  *(int *)(&stack0xffffffb8 + iVar7),
                                  *(LPWSTR *)(&stack0xffffffbc + iVar7),
                                  *(int *)((int)local_20 + iVar7 + -0x20));
      puVar5 = puVar11;
      if (iVar7 != 0) {
        *(LPWORD *)(puVar11 + -4) = param_4;
        *(int *)(puVar11 + -8) = iVar7;
        *(int **)(puVar11 + -0xc) = piVar6;
        *(DWORD *)(puVar11 + -0x10) = param_1;
        puVar5 = puVar11 + -0x14;
        *(undefined4 *)(puVar11 + -0x14) = 0x100ebf4;
        local_28 = GetStringTypeW(*(DWORD *)(puVar11 + -0x10),*(LPCWSTR *)(puVar11 + -0xc),
                                  *(int *)(puVar11 + -8),*(LPWORD *)(puVar11 + -4));
      }
      if (bVar1) {
        *(int **)(puVar5 + -4) = piVar6;
        *(undefined4 *)(puVar5 + -8) = 0x100ec03;
        FUN_0100a312(*(LPVOID *)(puVar5 + -4));
        return local_28;
      }
      return local_28;
    }
  }
  return 0;
}



// ========================================================
// Function: ___addl at 0100ec85
// ========================================================

/* Library Function - Single Match
    ___addl
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

undefined4 __cdecl ___addl(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = param_1 + param_2;
  uVar2 = 0;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    uVar2 = 1;
  }
  *param_3 = uVar1;
  return uVar2;
}



// ========================================================
// Function: FUN_0100ecae at 0100ecae
// ========================================================

void __cdecl FUN_0100ecae(uint *param_1,uint *param_2)

{
  int iVar1;
  
  iVar1 = ___addl(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = ___addl(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = ___addl(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  ___addl(param_1[2],param_2[2],param_1 + 2);
  return;
}



// ========================================================
// Function: FUN_0100ed15 at 0100ed15
// ========================================================

void __cdecl FUN_0100ed15(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = uVar1 * 2;
  param_1[1] = uVar2 * 2 | uVar1 >> 0x1f;
  param_1[2] = param_1[2] << 1 | uVar2 >> 0x1f;
  return;
}



// ========================================================
// Function: ___shr_12 at 0100ed4d
// ========================================================

/* Library Function - Single Match
    ___shr_12
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

void __cdecl ___shr_12(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}



// ========================================================
// Function: FUN_0100ed84 at 0100ed84
// ========================================================

void __cdecl FUN_0100ed84(char *param_1,int param_2,uint *param_3)

{
  short sVar1;
  uint uVar2;
  int local_20;
  char *local_1c;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_8 = DAT_0101107c;
  local_1c = param_1;
  sVar1 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    local_20 = param_2;
    do {
      local_14 = *param_3;
      local_10 = param_3[1];
      local_c = param_3[2];
      FUN_0100ed15(param_3);
      FUN_0100ed15(param_3);
      FUN_0100ecae(param_3,&local_14);
      FUN_0100ed15(param_3);
      local_14 = (uint)*local_1c;
      local_10 = 0;
      local_c = 0;
      FUN_0100ecae(param_3,&local_14);
      local_1c = local_1c + 1;
      local_20 = local_20 + -1;
    } while (local_20 != 0);
  }
  if (param_3[2] == 0) {
    do {
      sVar1 = sVar1 + -0x10;
      uVar2 = param_3[1] >> 0x10;
      param_3[1] = *param_3 >> 0x10 | param_3[1] << 0x10;
      *param_3 = *param_3 << 0x10;
    } while (uVar2 == 0);
    param_3[2] = uVar2;
  }
  while ((param_3[2] & 0x8000) == 0) {
    FUN_0100ed15(param_3);
    sVar1 = sVar1 + -1;
  }
  *(short *)((int)param_3 + 10) = sVar1;
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_0100ee6f at 0100ee6f
// ========================================================

void __cdecl
FUN_0100ee6f(undefined2 *param_1,int *param_2,byte *param_3,int param_4,int param_5,int param_6,
            int param_7)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  byte bVar7;
  undefined4 uVar8;
  byte *pbVar9;
  byte *pbVar10;
  int iVar11;
  int local_60;
  int local_50;
  byte *local_44;
  char *local_40;
  int local_3c;
  uint local_38;
  undefined2 local_34;
  undefined2 uStack_32;
  undefined2 uStack_30;
  undefined4 local_2e;
  ushort local_2a;
  char local_24 [23];
  char local_d;
  uint local_8;
  
  local_8 = DAT_0101107c;
  local_40 = local_24;
  uVar4 = 0;
  local_60 = 1;
  local_38 = 0;
  bVar1 = false;
  bVar3 = false;
  bVar2 = false;
  local_50 = 0;
  local_3c = 0;
  local_44 = param_3;
  for (; (((bVar7 = *param_3, bVar7 == 0x20 || (bVar7 == 9)) || (bVar7 == 10)) || (bVar7 == 0xd));
      param_3 = param_3 + 1) {
  }
  iVar11 = 0;
LAB_0100eed4:
  iVar6 = 1;
  bVar7 = *param_3;
  pbVar9 = param_3 + 1;
  pbVar10 = local_44;
  switch(iVar11) {
  case 0:
    if (('0' < (char)bVar7) && ((char)bVar7 < ':')) {
LAB_0100eef1:
      iVar11 = 3;
      goto LAB_0100f101;
    }
    if (bVar7 == DAT_0101138c) goto LAB_0100ef00;
    if (bVar7 == 0x2b) {
      uVar4 = 0;
      iVar11 = 2;
      param_3 = pbVar9;
    }
    else if (bVar7 == 0x2d) {
      uVar4 = 0x8000;
      iVar11 = 2;
      param_3 = pbVar9;
    }
    else {
      iVar11 = iVar6;
      param_3 = pbVar9;
      if (bVar7 != 0x30) goto LAB_0100ef1c;
    }
    goto LAB_0100eed4;
  case 1:
    bVar1 = true;
    if (('0' < (char)bVar7) && ((char)bVar7 < ':')) goto LAB_0100eef1;
    if (bVar7 == DAT_0101138c) goto LAB_0100effe;
    if ((bVar7 == 0x2b) || (bVar7 == 0x2d)) goto LAB_0100ef7a;
    iVar11 = iVar6;
    param_3 = pbVar9;
    if (bVar7 != 0x30) goto LAB_0100ef5f;
    goto LAB_0100eed4;
  case 2:
    if (('0' < (char)bVar7) && ((char)bVar7 < ':')) goto LAB_0100eef1;
    if (bVar7 == DAT_0101138c) {
LAB_0100ef00:
      iVar11 = 5;
      param_3 = pbVar9;
    }
    else {
      iVar11 = iVar6;
      param_3 = pbVar9;
      if (bVar7 != 0x30) goto LAB_0100f1db;
    }
    goto LAB_0100eed4;
  case 3:
    while( true ) {
      if (DAT_01011388 < 2) {
        uVar5 = (byte)PTR_DAT_01011394[(uint)bVar7 * 2] & 4;
      }
      else {
        uVar5 = __isctype((uint)bVar7,4);
      }
      if (uVar5 == 0) break;
      if (local_38 < 0x19) {
        local_38 = local_38 + 1;
        *local_40 = bVar7 - 0x30;
        local_40 = local_40 + 1;
      }
      else {
        local_3c = local_3c + 1;
      }
      bVar7 = *pbVar9;
      pbVar9 = pbVar9 + 1;
    }
    if (bVar7 != DAT_0101138c) goto LAB_0100f063;
LAB_0100effe:
    bVar1 = true;
    iVar11 = 4;
    param_3 = pbVar9;
    goto LAB_0100eed4;
  case 4:
    bVar3 = true;
    if (local_38 == 0) {
      while (bVar7 == 0x30) {
        local_3c = local_3c + -1;
        bVar7 = *pbVar9;
        pbVar9 = pbVar9 + 1;
      }
    }
    while( true ) {
      if (DAT_01011388 < 2) {
        uVar5 = (byte)PTR_DAT_01011394[(uint)bVar7 * 2] & 4;
      }
      else {
        uVar5 = __isctype((uint)bVar7,4);
      }
      if (uVar5 == 0) break;
      if (local_38 < 0x19) {
        local_38 = local_38 + 1;
        local_3c = local_3c + -1;
        *local_40 = bVar7 - 0x30;
        local_40 = local_40 + 1;
      }
      bVar7 = *pbVar9;
      pbVar9 = pbVar9 + 1;
    }
LAB_0100f063:
    if ((bVar7 == 0x2b) || (bVar7 == 0x2d)) {
LAB_0100ef7a:
      bVar1 = true;
      iVar11 = 0xb;
      param_3 = pbVar9 + -1;
    }
    else {
LAB_0100ef5f:
      bVar1 = true;
      if (((char)bVar7 < 'D') ||
         (('E' < (char)bVar7 && (((char)bVar7 < 'd' || ('e' < (char)bVar7)))))) goto LAB_0100ef1c;
      iVar11 = 6;
      param_3 = pbVar9;
    }
    goto LAB_0100eed4;
  case 5:
    bVar3 = true;
    if (DAT_01011388 < 2) {
      uVar5 = (byte)PTR_DAT_01011394[(uint)bVar7 * 2] & 4;
    }
    else {
      uVar5 = __isctype((uint)bVar7,4);
    }
    iVar11 = 4;
    if (uVar5 != 0) goto LAB_0100f101;
    goto LAB_0100f1db;
  case 6:
    local_44 = param_3 + -1;
    if (((char)bVar7 < '1') || ('9' < (char)bVar7)) {
      if (bVar7 == 0x2b) goto LAB_0100f134;
      if (bVar7 == 0x2d) goto LAB_0100f128;
LAB_0100f0cd:
      pbVar10 = local_44;
      if (bVar7 != 0x30) goto LAB_0100f1db;
      iVar11 = 8;
      param_3 = pbVar9;
      goto LAB_0100eed4;
    }
    break;
  case 7:
    if (((char)bVar7 < '1') || ('9' < (char)bVar7)) goto LAB_0100f0cd;
    break;
  case 8:
    bVar2 = true;
    while (bVar7 == 0x30) {
      bVar7 = *pbVar9;
      pbVar9 = pbVar9 + 1;
    }
    if (((char)bVar7 < '1') || ('9' < (char)bVar7)) goto LAB_0100ef1c;
    break;
  case 9:
    bVar2 = true;
    local_50 = 0;
    goto LAB_0100f15f;
  default:
    goto switchD_0100eee0_caseD_a;
  case 0xb:
    if (param_7 != 0) {
      local_44 = param_3;
      if (bVar7 == 0x2b) {
LAB_0100f134:
        iVar11 = 7;
        param_3 = pbVar9;
      }
      else {
        pbVar10 = param_3;
        if (bVar7 != 0x2d) goto LAB_0100f1db;
LAB_0100f128:
        local_60 = -1;
        iVar11 = 7;
        param_3 = pbVar9;
      }
      goto LAB_0100eed4;
    }
    iVar11 = 10;
    pbVar9 = param_3;
switchD_0100eee0_caseD_a:
    pbVar10 = pbVar9;
    param_3 = pbVar9;
    if (iVar11 != 10) goto LAB_0100eed4;
    goto LAB_0100f1db;
  }
  iVar11 = 9;
LAB_0100f101:
  param_3 = pbVar9 + -1;
  goto LAB_0100eed4;
LAB_0100f15f:
  if (DAT_01011388 < 2) {
    uVar5 = (byte)PTR_DAT_01011394[(uint)bVar7 * 2] & 4;
  }
  else {
    uVar5 = __isctype((uint)bVar7,4);
  }
  if (uVar5 == 0) goto LAB_0100f1a7;
  local_50 = (char)bVar7 + -0x30 + local_50 * 10;
  if (0x1450 < local_50) goto LAB_0100f19f;
  bVar7 = *pbVar9;
  pbVar9 = pbVar9 + 1;
  goto LAB_0100f15f;
LAB_0100f19f:
  local_50 = 0x1451;
LAB_0100f1a7:
  while( true ) {
    if (DAT_01011388 < 2) {
      uVar5 = (byte)PTR_DAT_01011394[(uint)bVar7 * 2] & 4;
    }
    else {
      uVar5 = __isctype((uint)bVar7,4);
    }
    if (uVar5 == 0) break;
    bVar7 = *pbVar9;
    pbVar9 = pbVar9 + 1;
  }
LAB_0100ef1c:
  pbVar10 = pbVar9 + -1;
LAB_0100f1db:
  *param_2 = (int)pbVar10;
  if (bVar1) {
    if (0x18 < local_38) {
      if ('\x04' < local_d) {
        local_d = local_d + '\x01';
      }
      local_38 = 0x18;
      local_40 = local_40 + -1;
      local_3c = local_3c + 1;
    }
    if (local_38 != 0) {
      while (local_40 = local_40 + -1, *local_40 == '\0') {
        local_38 = local_38 - 1;
        local_3c = local_3c + 1;
      }
      FUN_0100ed84(local_24,local_38,(uint *)&local_34);
      if (local_60 < 0) {
        local_50 = -local_50;
      }
      uVar5 = local_50 + local_3c;
      if (!bVar2) {
        uVar5 = uVar5 + param_5;
      }
      if (!bVar3) {
        uVar5 = uVar5 - param_6;
      }
      if (0x1450 < (int)uVar5) {
        uVar8 = 0;
        local_2a = 0x7fff;
        local_2e = 0x80000000;
        local_34 = 0;
        goto LAB_0100f2b0;
      }
      if (-0x1451 < (int)uVar5) {
        FUN_0100fbdf((int *)&local_34,uVar5,param_4);
        uVar8 = CONCAT22(uStack_30,uStack_32);
        goto LAB_0100f2b0;
      }
    }
  }
  local_34 = 0;
  local_2a = 0;
  local_2e = 0;
  uVar8 = 0;
LAB_0100f2b0:
  *param_1 = local_34;
  *(undefined4 *)(param_1 + 1) = uVar8;
  param_1[5] = local_2a | uVar4;
  *(undefined4 *)(param_1 + 3) = local_2e;
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_0100f307 at 0100f307
// ========================================================

void __cdecl
FUN_0100f307(uint param_1,uint param_2,ushort param_3,int param_4,byte param_5,short *param_6)

{
  short *psVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  short *psVar5;
  short *psVar6;
  short sVar7;
  int iVar8;
  char *pcVar9;
  int local_38;
  short *local_30;
  uint local_2c;
  uint local_28;
  undefined4 local_24;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined2 local_14;
  undefined4 local_12;
  undefined4 local_e;
  undefined1 local_a;
  char cStack_9;
  uint local_8;
  
  local_2c = param_1;
  local_28 = param_2;
  local_8 = DAT_0101107c;
  local_24 = CONCAT22(local_24._2_2_,param_3);
  uVar4 = param_3 & 0x7fff;
  local_20 = 0xcc;
  local_1f = 0xcc;
  local_1e = 0xcc;
  local_1d = 0xcc;
  local_1c = 0xcc;
  local_1b = 0xcc;
  local_1a = 0xcc;
  local_19 = 0xcc;
  local_18 = 0xcc;
  local_17 = 0xcc;
  local_16 = 0xfb;
  local_15 = 0x3f;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar4 == 0) && (param_2 == 0)) && (param_1 == 0)) {
LAB_0100f489:
    *(undefined1 *)(param_6 + 2) = 0x30;
LAB_0100f58c:
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)((int)param_6 + 5) = 0;
  }
  else {
    if ((short)uVar4 == 0x7fff) {
      *param_6 = 1;
      if (((param_2 == 0x80000000) && (param_1 == 0)) || ((param_2 & 0x40000000) != 0)) {
        if (((param_3 & 0x8000) == 0) || (param_2 != 0xc0000000)) {
          if ((param_2 != 0x80000000) || (param_1 != 0)) goto LAB_0100f3ff;
          pcVar9 = "1#INF";
        }
        else {
          if (param_1 != 0) {
LAB_0100f3ff:
            pcVar9 = "1#QNAN";
            goto LAB_0100f404;
          }
          pcVar9 = "1#IND";
        }
        FID_conflict___mbscpy((char *)(param_6 + 2),pcVar9);
        *(undefined1 *)((int)param_6 + 3) = 5;
      }
      else {
        pcVar9 = "1#SNAN";
LAB_0100f404:
        FID_conflict___mbscpy((char *)(param_6 + 2),pcVar9);
        *(undefined1 *)((int)param_6 + 3) = 6;
      }
      goto LAB_0100f56e;
    }
    local_14 = 0;
    sVar7 = (short)(((uVar4 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar4 * 0x4d10 >>
                   0x10);
    local_a = (undefined1)uVar4;
    cStack_9 = (char)(uVar4 >> 8);
    local_12 = param_1;
    local_e = param_2;
    FUN_0100fbdf((int *)&local_14,-(int)sVar7,1);
    if (0x3ffe < CONCAT11(cStack_9,local_a)) {
      sVar7 = sVar7 + 1;
      FUN_0100f9a6((int *)&local_14,(int *)&local_20);
    }
    *param_6 = sVar7;
    if (((param_5 & 1) != 0) && (param_4 = param_4 + sVar7, param_4 < 1)) goto LAB_0100f489;
    if (0x15 < param_4) {
      param_4 = 0x15;
    }
    iVar8 = CONCAT11(cStack_9,local_a) - 0x3ffe;
    local_a = 0;
    cStack_9 = '\0';
    local_30 = (short *)0x8;
    do {
      FUN_0100ed15((uint *)&local_14);
      local_30 = (short *)((int)local_30 + -1);
    } while (local_30 != (short *)0x0);
    if (iVar8 < 0) {
      for (uVar4 = -iVar8 & 0xff; uVar4 != 0; uVar4 = uVar4 - 1) {
        ___shr_12((uint *)&local_14);
      }
    }
    local_38 = param_4 + 1;
    psVar5 = param_6 + 2;
    local_30 = psVar5;
    uVar4 = local_12;
    uVar2 = local_e;
    if (0 < local_38) {
      do {
        local_e._2_2_ = (undefined2)(uVar2 >> 0x10);
        local_e._0_2_ = (undefined2)uVar2;
        local_12._2_2_ = (undefined2)(uVar4 >> 0x10);
        local_12._0_2_ = (undefined2)uVar4;
        local_2c = CONCAT22((undefined2)local_12,local_14);
        local_28 = CONCAT22((undefined2)local_e,local_12._2_2_);
        local_24 = CONCAT13(cStack_9,CONCAT12(local_a,local_e._2_2_));
        local_12 = uVar4;
        local_e = uVar2;
        FUN_0100ed15((uint *)&local_14);
        FUN_0100ed15((uint *)&local_14);
        FUN_0100ecae((uint *)&local_14,&local_2c);
        FUN_0100ed15((uint *)&local_14);
        psVar5 = (short *)((int)local_30 + 1);
        local_38 = local_38 + -1;
        *(char *)local_30 = cStack_9 + '0';
        cStack_9 = '\0';
        local_30 = psVar5;
        uVar4 = local_12;
        uVar2 = local_e;
      } while (local_38 != 0);
    }
    psVar6 = psVar5 + -1;
    psVar1 = param_6 + 2;
    if (*(char *)((int)psVar5 + -1) < '5') {
      for (; (psVar1 <= psVar6 && ((char)*psVar6 == '0')); psVar6 = (short *)((int)psVar6 + -1)) {
      }
      if (psVar6 < psVar1) {
        *(char *)psVar1 = '0';
        goto LAB_0100f58c;
      }
    }
    else {
      for (; (psVar1 <= psVar6 && ((char)*psVar6 == '9')); psVar6 = (short *)((int)psVar6 + -1)) {
        *(char *)psVar6 = '0';
      }
      if (psVar6 < psVar1) {
        psVar6 = (short *)((int)psVar6 + 1);
        *param_6 = *param_6 + 1;
      }
      *(char *)psVar6 = (char)*psVar6 + '\x01';
    }
    cVar3 = ((char)psVar6 - (char)param_6) + -3;
    *(char *)((int)param_6 + 3) = cVar3;
    *(undefined1 *)(cVar3 + 4 + (int)param_6) = 0;
  }
LAB_0100f56e:
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: __fpclass at 0100f5a6
// ========================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __fpclass
   
   Library: Visual Studio 2003 Release */

int __cdecl __fpclass(double _X)

{
  int iVar1;
  
  if ((_X._6_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = __sptype(_X._0_4_,(uint)((ulonglong)_X >> 0x20));
    if (iVar1 == 1) {
      return 0x200;
    }
    if (iVar1 == 2) {
      iVar1 = 4;
    }
    else {
      if (iVar1 != 3) {
        return 1;
      }
      iVar1 = 2;
    }
    return iVar1;
  }
  if ((((ulonglong)_X & 0x7ff0000000000000) == 0) &&
     ((((ulonglong)_X & 0xfffff00000000) != 0 || (_X._0_4_ != 0)))) {
    return (-(uint)(((ulonglong)_X & 0x8000000000000000) != 0) & 0xffffff90) + 0x80;
  }
  if (_X == _DAT_01001a38) {
    return (-(uint)(((ulonglong)_X & 0x8000000000000000) != 0) & 0xffffffe0) + 0x40;
  }
  return (-(uint)(((ulonglong)_X & 0x8000000000000000) != 0) & 0xffffff08) + 0x100;
}



// ========================================================
// Function: ___ansicp at 0100f649
// ========================================================

/* Library Function - Single Match
    ___ansicp
   
   Library: Visual Studio 2003 Release */

void __cdecl ___ansicp(LCID param_1)

{
  int iVar1;
  byte local_10 [6];
  undefined1 local_a;
  uint local_8;
  
  local_8 = DAT_0101107c;
  local_a = 0;
  iVar1 = GetLocaleInfoA(param_1,0x1004,(LPSTR)local_10,6);
  if (iVar1 != 0) {
    FUN_0100fc70(local_10);
  }
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_0100f693 at 0100f693
// ========================================================

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

void __cdecl
FUN_0100f693(UINT param_1,UINT param_2,LPCSTR param_3,int *param_4,LPSTR param_5,int param_6)

{
  char cVar1;
  char *cbMultiByte;
  bool bVar2;
  bool bVar3;
  BOOL BVar4;
  LPCSTR pCVar5;
  int iVar6;
  int *lpMultiByteStr;
  uint uVar7;
  undefined4 *puVar8;
  LPCWSTR local_54;
  char *local_40;
  _cpinfo local_34;
  uint local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_010025c8;
  uStack_c = 0x100f69f;
  local_20 = DAT_0101107c;
  bVar3 = false;
  cbMultiByte = (char *)*param_4;
  bVar2 = false;
  if (param_1 != param_2) {
    BVar4 = GetCPInfo(param_1,&local_34);
    if ((((BVar4 != 0) && (local_34.MaxCharSize == 1)) &&
        (BVar4 = GetCPInfo(param_2,&local_34), BVar4 != 0)) && (local_34.MaxCharSize == 1)) {
      bVar2 = true;
    }
    if ((bVar2) && (local_40 = cbMultiByte, cbMultiByte == (char *)0xffffffff)) {
      pCVar5 = param_3;
      do {
        cVar1 = *pCVar5;
        pCVar5 = pCVar5 + 1;
      } while (cVar1 != '\0');
      local_40 = pCVar5 + (1 - (int)(param_3 + 1));
    }
    if ((!bVar2) &&
       (local_40 = (char *)MultiByteToWideChar(param_1,1,param_3,(int)cbMultiByte,(LPWSTR)0x0,0),
       local_40 == (char *)0x0)) goto LAB_0100f86c;
    local_1c = &stack0xffffff9c;
    local_54 = (LPCWSTR)&stack0xffffff9c;
    puVar8 = (undefined4 *)&stack0xffffff9c;
    for (uVar7 = ((uint)local_40 & 0x7fffffff) >> 1; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar8 = 0;
      puVar8 = puVar8 + 1;
    }
    for (uVar7 = (int)local_40 * 2 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined1 *)puVar8 = 0;
      puVar8 = (undefined4 *)((int)puVar8 + 1);
    }
    local_8 = (undefined *)0xffffffff;
    if (&stack0x00000000 == (undefined1 *)0x64) {
      local_54 = (LPCWSTR)FUN_0100f906(2,(uint)local_40);
      if (local_54 == (LPCWSTR)0x0) goto LAB_0100f86c;
      bVar3 = true;
    }
    iVar6 = MultiByteToWideChar(param_1,1,param_3,(int)cbMultiByte,local_54,(int)local_40);
    if (iVar6 != 0) {
      if (param_5 == (LPSTR)0x0) {
        if (((bVar2) ||
            (local_40 = (char *)WideCharToMultiByte(param_2,0,local_54,(int)local_40,(LPSTR)0x0,0,
                                                    (LPCSTR)0x0,(LPBOOL)0x0),
            local_40 != (char *)0x0)) &&
           (lpMultiByteStr = FUN_0100f906(1,(uint)local_40), lpMultiByteStr != (int *)0x0)) {
          iVar6 = WideCharToMultiByte(param_2,0,local_54,(int)local_40,(LPSTR)lpMultiByteStr,
                                      (int)local_40,(LPCSTR)0x0,(LPBOOL)0x0);
          if (iVar6 == 0) {
            FUN_0100a312(lpMultiByteStr);
          }
          else if (cbMultiByte != (char *)0xffffffff) {
            *param_4 = iVar6;
          }
        }
      }
      else {
        WideCharToMultiByte(param_2,0,local_54,(int)local_40,param_5,param_6,(LPCSTR)0x0,(LPBOOL)0x0
                           );
      }
    }
  }
  if (bVar3) {
    FUN_0100a312(local_54);
  }
LAB_0100f86c:
  FUN_01008e6b(local_20);
  return;
}



// ========================================================
// Function: FUN_0100f882 at 0100f882
// ========================================================

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

BOOL FUN_0100f882(void)

{
  SIZE_T SVar1;
  BOOL BVar2;
  LPVOID lpAddress;
  undefined4 uStack_58;
  _SYSTEM_INFO local_48;
  _MEMORY_BASIC_INFORMATION local_24;
  DWORD local_8;
  
  uStack_58 = 0x100f895;
  SVar1 = VirtualQuery(&uStack_58,&local_24,0x1c);
  if (SVar1 != 0) {
    GetSystemInfo(&local_48);
    lpAddress = (LPVOID)((~(local_48.dwPageSize - 1) & (uint)&uStack_58) - local_48.dwPageSize);
    if ((LPVOID)(((-(uint)(DAT_0101306c != 1) & 0xfffffff1) + 0x11) * local_48.dwPageSize +
                (int)local_24.AllocationBase) <= lpAddress) {
      BVar2 = VirtualProtect(lpAddress,local_48.dwPageSize,(-(uint)(DAT_0101306c != 1) & 0x103) + 1,
                             &local_8);
      return BVar2;
    }
  }
  return 0;
}



// ========================================================
// Function: FUN_0100f906 at 0100f906
// ========================================================

int * __cdecl FUN_0100f906(uint param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint *dwBytes;
  int *piVar5;
  
  if ((param_1 != 0) && (0xffffffe0 / param_1 < param_2)) {
    return (int *)0x0;
  }
  puVar3 = (uint *)(param_1 * param_2);
  dwBytes = puVar3;
  if (puVar3 == (uint *)0x0) {
    dwBytes = (uint *)0x1;
  }
  do {
    if (dwBytes < (uint *)0xffffffe1) {
      if (((DAT_0101352c == 3) &&
          (dwBytes = (uint *)((int)dwBytes + 0xfU & 0xfffffff0),
          puVar3 < DAT_010132cc || (int)puVar3 - (int)DAT_010132cc == 0)) &&
         (piVar1 = ___sbh_alloc_block(puVar3), piVar1 != (int *)0x0)) {
        piVar5 = piVar1;
        for (uVar4 = (uint)puVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *piVar5 = 0;
          piVar5 = piVar5 + 1;
        }
        for (uVar4 = (uint)puVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined1 *)piVar5 = 0;
          piVar5 = (int *)((int)piVar5 + 1);
        }
        return piVar1;
      }
      piVar1 = HeapAlloc(DAT_01013528,8,(SIZE_T)dwBytes);
      if (piVar1 != (int *)0x0) {
        return piVar1;
      }
    }
    if (DAT_01013284 == 0) {
      return (int *)0x0;
    }
    iVar2 = FUN_0100d898(dwBytes);
  } while (iVar2 != 0);
  return (int *)0x0;
}



// ========================================================
// Function: FUN_0100f9a6 at 0100f9a6
// ========================================================

void __cdecl FUN_0100f9a6(int *param_1,int *param_2)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  ushort uVar6;
  uint uVar7;
  ushort uVar8;
  int local_34;
  int local_30;
  ushort *local_2c;
  int local_28;
  ushort *local_24;
  short *local_20;
  int local_1c;
  ushort local_18;
  byte local_14;
  undefined1 uStack_13;
  undefined4 uStack_12;
  undefined4 uStack_e;
  undefined2 uStack_a;
  uint local_8;
  
  local_8 = DAT_0101107c;
  local_28 = 0;
  local_14 = 0;
  uStack_13 = 0;
  uStack_12._0_2_ = 0;
  uStack_12._2_2_ = 0;
  uStack_e._0_2_ = 0;
  uStack_e._2_2_ = 0;
  uStack_a._0_1_ = 0;
  uStack_a._1_1_ = 0;
  uVar6 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar4 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar8 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar3 = uVar6 + uVar4;
  iVar5 = 0;
  iVar2 = 0;
  sVar1 = 0;
  if (((uVar4 < 0x7fff) && (iVar5 = 0, iVar2 = 0, sVar1 = 0, uVar6 < 0x7fff)) &&
     (iVar5 = 0, iVar2 = 0, sVar1 = 0, uVar3 < 0xbffe)) {
    if (uVar3 < 0x3fc0) {
LAB_0100fa55:
      param_1[2] = 0;
      param_1[1] = 0;
      *param_1 = 0;
      iVar5 = 0;
      iVar2 = 0;
      sVar1 = 0;
      goto LAB_0100fbcd;
    }
    if (uVar4 == 0) {
      uVar3 = uVar3 + 1;
      local_18 = 0;
      if ((((param_1[2] & 0x7fffffffU) != 0) || (param_1[1] != 0)) ||
         (iVar5 = 0, iVar2 = 0, sVar1 = 0, *param_1 != 0)) goto LAB_0100fa3f;
    }
    else {
LAB_0100fa3f:
      if (((uVar6 == 0) && (uVar3 = uVar3 + 1, (param_2[2] & 0x7fffffffU) == 0)) &&
         ((param_2[1] == 0 && (*param_2 == 0)))) goto LAB_0100fa55;
      local_30 = 0;
      local_20 = (short *)((int)&uStack_12 + 2);
      local_1c = 5;
      do {
        if (0 < local_1c) {
          local_2c = (ushort *)(local_30 * 2 + (int)param_1);
          local_24 = (ushort *)(param_2 + 2);
          local_34 = local_1c;
          do {
            iVar5 = ___addl(*(uint *)(local_20 + -2),(uint)*local_24 * (uint)*local_2c,
                            (uint *)(local_20 + -2));
            if (iVar5 != 0) {
              *local_20 = *local_20 + 1;
            }
            local_2c = local_2c + 1;
            local_24 = local_24 + -1;
            local_34 = local_34 + -1;
          } while (local_34 != 0);
        }
        local_20 = local_20 + 1;
        local_30 = local_30 + 1;
        local_1c = local_1c + -1;
      } while (0 < local_1c);
      local_18 = uVar3 + 0xc002;
      if ((short)local_18 < 1) {
LAB_0100fb09:
        local_18 = local_18 - 1;
        if ((short)local_18 < 0) {
          uVar7 = (uint)(ushort)-local_18;
          local_18 = 0;
          do {
            if ((local_14 & 1) != 0) {
              local_28 = local_28 + 1;
            }
            ___shr_12((uint *)&local_14);
            uVar7 = uVar7 - 1;
          } while (uVar7 != 0);
          if (local_28 != 0) {
            local_14 = local_14 | 1;
          }
        }
      }
      else {
        do {
          if ((uStack_a._1_1_ & 0x80) != 0) break;
          FUN_0100ed15((uint *)&local_14);
          local_18 = local_18 - 1;
        } while (0 < (short)local_18);
        if ((short)local_18 < 1) goto LAB_0100fb09;
      }
      if ((0x8000 < CONCAT11(uStack_13,local_14)) ||
         (sVar1 = CONCAT11(uStack_a._1_1_,(undefined1)uStack_a),
         iVar2 = CONCAT22(uStack_e._2_2_,(undefined2)uStack_e),
         iVar5 = CONCAT22(uStack_12._2_2_,(undefined2)uStack_12),
         (CONCAT22((undefined2)uStack_12,CONCAT11(uStack_13,local_14)) & 0x1ffff) == 0x18000)) {
        if (CONCAT22(uStack_12._2_2_,(undefined2)uStack_12) == -1) {
          iVar5 = 0;
          if (CONCAT22(uStack_e._2_2_,(undefined2)uStack_e) == -1) {
            if (CONCAT11(uStack_a._1_1_,(undefined1)uStack_a) == -1) {
              local_18 = local_18 + 1;
              sVar1 = -0x8000;
              iVar2 = 0;
              iVar5 = 0;
            }
            else {
              sVar1 = CONCAT11(uStack_a._1_1_,(undefined1)uStack_a) + 1;
              iVar2 = 0;
              iVar5 = 0;
            }
          }
          else {
            sVar1 = CONCAT11(uStack_a._1_1_,(undefined1)uStack_a);
            iVar2 = CONCAT22(uStack_e._2_2_,(undefined2)uStack_e) + 1;
          }
        }
        else {
          iVar5 = CONCAT22(uStack_12._2_2_,(undefined2)uStack_12) + 1;
          sVar1 = CONCAT11(uStack_a._1_1_,(undefined1)uStack_a);
          iVar2 = CONCAT22(uStack_e._2_2_,(undefined2)uStack_e);
        }
      }
      uStack_12._2_2_ = (undefined2)((uint)iVar5 >> 0x10);
      uStack_12._0_2_ = (undefined2)iVar5;
      uStack_e._2_2_ = (undefined2)((uint)iVar2 >> 0x10);
      uStack_e._0_2_ = (undefined2)iVar2;
      uStack_a._1_1_ = (byte)((ushort)sVar1 >> 8);
      uStack_a._0_1_ = (undefined1)sVar1;
      if (0x7ffe < local_18) goto LAB_0100fbb2;
      *(undefined2 *)param_1 = (undefined2)uStack_12;
      *(uint *)((int)param_1 + 2) = CONCAT22((undefined2)uStack_e,uStack_12._2_2_);
      *(uint *)((int)param_1 + 6) =
           CONCAT13(uStack_a._1_1_,CONCAT12((undefined1)uStack_a,uStack_e._2_2_));
      local_18 = local_18 | uVar8;
    }
    *(ushort *)((int)param_1 + 10) = local_18;
  }
  else {
LAB_0100fbb2:
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar8 != 0) & 0x80000000) + 0x7fff8000;
  }
LAB_0100fbcd:
  uStack_12 = iVar5;
  uStack_e = iVar2;
  uStack_a = sVar1;
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_0100fbdf at 0100fbdf
// ========================================================

void __cdecl FUN_0100fbdf(int *param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ushort *puVar4;
  ushort local_14;
  undefined4 local_12;
  undefined2 uStack_e;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_0101107c;
  iVar3 = 0x10114d8;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      iVar3 = 0x1011638;
    }
    if (param_3 == 0) {
      *(undefined2 *)param_1 = 0;
    }
    while (param_2 != 0) {
      uVar1 = (int)param_2 >> 3;
      uVar2 = param_2 & 7;
      iVar3 = iVar3 + 0x54;
      param_2 = uVar1;
      if (uVar2 != 0) {
        puVar4 = (ushort *)(iVar3 + uVar2 * 0xc);
        if (0x7fff < *puVar4) {
          local_14 = (ushort)*(undefined4 *)puVar4;
          local_12._0_2_ = (undefined2)((uint)*(undefined4 *)puVar4 >> 0x10);
          local_12._2_2_ = (undefined2)*(undefined4 *)(puVar4 + 2);
          uStack_e = (undefined2)((uint)*(undefined4 *)(puVar4 + 2) >> 0x10);
          uStack_c = *(undefined4 *)(puVar4 + 4);
          local_12 = CONCAT22(local_12._2_2_,(undefined2)local_12) + -1;
          puVar4 = &local_14;
        }
        FUN_0100f9a6(param_1,(int *)puVar4);
      }
    }
  }
  FUN_01008e6b(local_8);
  return;
}



// ========================================================
// Function: FUN_0100fc70 at 0100fc70
// ========================================================

int __cdecl FUN_0100fc70(byte *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  
  if (param_1 == (byte *)0x0) {
    iVar1 = 0;
  }
  else {
    while( true ) {
      if (DAT_01011388 < 2) {
        uVar2 = (byte)PTR_DAT_01011394[(uint)*param_1 * 2] & 8;
      }
      else {
        uVar2 = __isctype((uint)*param_1,8);
      }
      if (uVar2 == 0) break;
      param_1 = param_1 + 1;
    }
    uVar2 = (uint)*param_1;
    pbVar5 = param_1 + 1;
    if ((uVar2 == 0x2d) || (uVar3 = uVar2, uVar2 == 0x2b)) {
      uVar3 = (uint)*pbVar5;
      pbVar5 = param_1 + 2;
    }
    iVar1 = 0;
    while( true ) {
      if ((uVar3 < 0x30) || (0x39 < uVar3)) {
        iVar4 = -1;
      }
      else {
        iVar4 = uVar3 - 0x30;
      }
      if (iVar4 == -1) break;
      iVar1 = iVar4 + iVar1 * 10;
      uVar3 = (uint)*pbVar5;
      pbVar5 = pbVar5 + 1;
    }
    if (uVar2 == 0x2d) {
      iVar1 = -iVar1;
    }
  }
  return iVar1;
}



// ========================================================
// Function: RtlUnwind at 0100fd3a
// ========================================================

void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    /* WARNING: Could not recover jumptable at 0x0100fd3a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}



// ========================================================
// Function: GetRegisteredLocation at 0100fd45
// ========================================================

/* Library Function - Single Match
    int __stdcall GetRegisteredLocation(char *)
   
   Library: Visual Studio 2005 Release */

int GetRegisteredLocation(char *param_1)

{
  LSTATUS LVar1;
  uint uVar2;
  DWORD local_c;
  HKEY local_8;
  
  LVar1 = RegOpenKeyExA((HKEY)0x80000000,
                        "CLSID\\{ADB880A6-D8FF-11CF-9377-00AA003B7A11}\\InprocServer32",0,0x20019,
                        &local_8);
  if (LVar1 == 0) {
    local_c = 0x104;
    LVar1 = RegQueryValueExA(local_8,"",(LPDWORD)0x0,(LPDWORD)0x0,(LPBYTE)param_1,&local_c);
    uVar2 = (uint)(LVar1 == 0);
    RegCloseKey(local_8);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ========================================================
// Function: _HtmlHelpW@16 at 0100fda9
// ========================================================

/* Library Function - Single Match
    _HtmlHelpW@16
   
   Library: Visual Studio 2005 Release */

void _HtmlHelpW_16(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  char local_10c [260];
  uint local_8;
  
  local_8 = DAT_0101107c;
  if ((DAT_010132bc == (HMODULE)0x0) && (DAT_010132b8 == 0)) {
    iVar1 = GetRegisteredLocation(local_10c);
    if (iVar1 != 0) {
      DAT_010132bc = LoadLibraryA(local_10c);
    }
    if (DAT_010132bc != (HMODULE)0x0) goto LAB_0100fe18;
    DAT_010132bc = LoadLibraryA("hhctrl.ocx");
    if (DAT_010132bc != (HMODULE)0x0) goto LAB_0100fe18;
LAB_0100fe33:
    DAT_010132b8 = 1;
  }
  else {
LAB_0100fe18:
    if (DAT_010132b4 == (FARPROC)0x0) {
      DAT_010132b4 = GetProcAddress(DAT_010132bc,(LPCSTR)0xf);
      if (DAT_010132b4 == (FARPROC)0x0) goto LAB_0100fe33;
    }
    (*DAT_010132b4)(param_1,param_2,param_3,param_4);
  }
  FUN_01008e6b(local_8);
  return;
}



