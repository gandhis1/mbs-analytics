using System;
using System.ComponentModel.DataAnnotations;

namespace frontend
{
    public enum DealType
    {
        [Display(Name = "Freddie STACR Credit Risk Transfer (CRT)")]
        FreddieSTACRCreditRiskTransfer,
        [Display(Name = "Fannie CAS Credit Risk Transfer (CRT)")]
        FannieCASCreditRiskTransfer,
        [Display(Name = "Fannie DUS Multifamily Pool")]
        FannieDUSMultifamilyPool
    }
    public class DataLoader
    {

    }
}