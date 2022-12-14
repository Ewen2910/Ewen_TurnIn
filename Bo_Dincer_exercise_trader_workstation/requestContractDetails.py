from ibapi.client import *
from ibapi.wrapper import *
import time
import datetime
import os

class TWSApp(EClient, EWrapper):
    def __init__(self, list_ConId, list_Exchange):
        EClient.__init__(self, self)
        self.Contract_conId = list_ConId
        self.Contract_exchange = list_Exchange
        self.CON_ID = 0
        self.TICKER = 0
        self.PRICE = 0
        self.BAR_COUNT = 0
        self.VOLUME = 0
        self.HIGH_PRICE = 0 
        self.LOW_PRICE = 0
        self.CURRENT_PRICE = 0
        self.WAP = 0
        self.VWAP = "Not accessible (paid version required)"
    
    def nextValidId(self, orderId: int):
        myContract = Contract()
        myContract.conId = self.Contract_conId
        myContract.exchange = self.Contract_exchange
        if myContract.exchange == "PAXOS":
            myContract.secType = "CRYPTO"
        self.reqMarketDataType(4)
        self.reqMktData(orderId, myContract, "100", 0, 0, [])
        queryTime = (datetime.datetime.today()).strftime("%Y%m%d-%H:%M:%S")
        self.reqHistoricalData(orderId, myContract, queryTime, "1 M", "1 day", "TRADES", 1, 1, False, [])
        time.sleep(3)
        self.reqContractDetails(1, myContract)

    def contractDetails(self, reqId, contractDetails):
        self.CON_ID = contractDetails.contract.conId
        self.TICKER = contractDetails.contract.symbol
        
    def tickPrice(self, reqId, tickType, price, attrib):
        if tickType == TickTypeEnum.DELAYED_LAST or tickType == 4:
            self.PRICE = price
        if tickType == TickTypeEnum.DELAYED_HIGH or tickType == 6:
            self.HIGH_PRICE = price
        if tickType == TickTypeEnum.DELAYED_LOW or tickType == 7:
            self.LOW_PRICE = price
        if tickType == TickTypeEnum.DELAYED_ASK or tickType == 2:
            self.CURRENT_PRICE = price

    def historicalData(self, reqId, bar):
        self.BAR_COUNT = bar.barCount
        self.VOLUME = bar.volume
        self.WAP = bar.wap

    def contractDetailsEnd(self, reqId):
        self.disconnect()

def main():
    list_ConId = [265598, 272093, 76792991, 312496724, 107113386, 9599491, 208813719, 4815747]
    list_ConId_crypto = [479624278, 495759171]
    list_Exchange = ["SMART", "PAXOS"]
    i = 0
    if os.path.exists("TWS_result.txt"):
        os.remove("TWS_result.txt")
    f = open("TWS_result.txt", 'w')
    while i != len(list_ConId):
        app = TWSApp(list_ConId[i], list_Exchange[0])
        app.connect("127.0.0.1", 7497, 1000)
        app.run()
        f.write("A. conId:" + " " + str(app.CON_ID) + "\n")
        f.write("B. TICKER:" + " " + str(app.TICKER) + "\n")
        f.write("C. PRICE:" + " " + str(app.PRICE) + "\n")
        f.write("D. BAR_COUNT:" + " " + str(app.BAR_COUNT) + "\n")
        f.write("E. VOLUME:" + " " + str(app.VOLUME) + "\n")
        f.write("F. HIGH_PRICE:" + " " + str(app.HIGH_PRICE) + "\n")
        f.write("G. LOW_PRICE:" + " " + str(app.LOW_PRICE) + "\n")
        f.write("H. CURRENT_PRICE:" + " " + str(app.CURRENT_PRICE) + "\n")
        f.write("I. WAP:" + " " + str(app.WAP) + "\n")
        f.write("J. VWAP:" + " " + str(app.VWAP) + "\n")
        f.write("\n")
        i += 1
    j = 0
    while j != len(list_ConId_crypto):
        app = TWSApp(list_ConId_crypto[j], list_Exchange[1])
        app.connect("127.0.0.1", 7496, 1000)
        app.run()
        f.write("A. conId:" + " " + str(app.CON_ID) + "\n")
        f.write("B. TICKER:" + " " + str(app.TICKER) + "\n")
        f.write("C. PRICE:" + " " + str(app.PRICE) + "\n")
        f.write("D. BAR_COUNT:" + " " + str(app.BAR_COUNT) + "\n")
        f.write("E. VOLUME:" + " " + str(app.VOLUME) + "\n")
        f.write("F. HIGH_PRICE:" + " " + str(app.HIGH_PRICE) + "\n")
        f.write("G. LOW_PRICE:" + " " + str(app.LOW_PRICE) + "\n")
        f.write("H. CURRENT_PRICE:" + " " + str(app.CURRENT_PRICE) + "\n")
        f.write("I. WAP:" + " " + str(app.WAP) + "\n")
        f.write("J. VWAP:" + " " + str(app.VWAP) + "\n")
        f.write("\n")
        j += 1
    f.close()

    print("A. conId:", app.CON_ID)
    print("B. TICKER:", app.TICKER)
    print("C. PRICE:", app.PRICE)
    print("D. BAR_COUNT:", app.BAR_COUNT)
    print("E. VOLUME:", app.VOLUME)
    print("F. HIGH_PRICE:", app.HIGH_PRICE)
    print("G. LOW_PRICE:", app.LOW_PRICE)
    print("H. CURRENT_PRICE:", app.CURRENT_PRICE)
    print("I. WAP:", app.WAP)
    print("J. VWAP:", app.VWAP)

if __name__ == "__main__":
    main()