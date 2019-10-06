using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.IO;
using System.Net;
using System.Net.Http;

using ExtensionMethods;

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
    public static class Data
    {
        private static Dictionary<DealType, DataLoader> singletonCache = new Dictionary<DealType, DataLoader>();
        private static readonly string cookiePath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "MBS Analytics", "cookies.dat");
        private static readonly CookieContainer cookies;
        private static readonly Finalizer finalizer = new Finalizer();
        private static readonly HttpClientHandler httpClientHandler = new HttpClientHandler() { CookieContainer = cookies };
        public static readonly HttpClient HttpClient = new HttpClient(httpClientHandler);

        static Data()
        {
            if (File.Exists(cookiePath))
            {
                cookies.LoadFromFile(cookiePath);
            }
        }

        private class Finalizer
        {
            ~Finalizer()
            {
                Data.cookies.SaveToFile(Data.cookiePath);
            }
        }

        public static DataLoader GetDataLoader(DealType dealType)
        {
            if (singletonCache.ContainsKey(dealType))
            {
                return singletonCache[dealType];
            }
            else if (dealType == DealType.FannieDUSMultifamilyPool)
            {
                return new FannieDUSMultifamilyPoolLoader();
            }
            else {
                throw new NotImplementedException(String.Format("Loading of collateral data for {0} is not yet implemented", dealType.ToString()));
            }
        }
    }


    public abstract class DataLoader
    {
        public abstract Deal LoadDeal(string dealName);
    }

    public class FannieDUSMultifamilyPoolLoader: DataLoader
    {
        private readonly string loginURL = "";
        private readonly string poolSearchURL = "https://mfdusdisclose.fanniemae.com/service/search/quick/";

        private void logIntoDUSDisclose()
        {
            Console.WriteLine("DUS Disclose Username: ");
            var username = Console.ReadLine();
            Console.WriteLine("DUS Disclose Password: ");
            var password = Console.ReadLine();
            var authContent = new FormUrlEncodedContent(new[]
                {
                    new KeyValuePair<string, string>("EmailAddress", username),
                    new KeyValuePair<string, string>("password", password)
                }
            );
            Data.HttpClient.PostAsync(loginURL, authContent).Result.EnsureSuccessStatusCode();
        }

        private string getDUSDiscloseTransactionID(string dealName, bool throwOnFailure = false)
        {
            var response  = Data.HttpClient.GetAsync(poolSearchURL + dealName).Result;
            Console.WriteLine(response.StatusCode);
            if (!response.IsSuccessStatusCode)
            {
                if (throwOnFailure)
                {
                    response.EnsureSuccessStatusCode();
                }
                logIntoDUSDisclose();
                return getDUSDiscloseTransactionID(dealName, throwOnFailure: true);
            }
            return "26141";

        }

        public override Deal LoadDeal(string dealName)
        {
            


            var deal = new Deal(dealName);
            for (int i = 1; i < 60; i++)
            {
                Loan loan = new Loan(
                    loanId: "1717469130",
                    originalBalance: 763000.0,
                    currentBalance: 763000.0,
                    factorDate: new DateTime(2019, 2, 1),
                    originalLoanTerm: 60,
                    originalAmortTerm: 360,
                    originalIOTerm: 0,
                    currentLoanAge: i,
                    grossCoupon: 0.0496,
                    feeStrip: 0.0248,
                    accrualBasis: AccrualBasis.ACTUAL_360,
                    originalPrepaymentString: "YM(54) O(6)"
                );
                deal.AddLoanToDeal(loan);
            }
            return deal;
        }
    }

}