#!/usr/bin/env python3
# encoding: utf-8
# cryptoanalyse.py
# Created by pyT0f on 24/06/2018.
    
import os
import numpy as np
import pandas as pd
import pickle
import ccxt
import matplotlib.pyplot as plt 
from datetime import datetime
pd.set_option('display.max_columns', 11)
altcoinsData = {}
def getCCXTData(market):
    '''télécharge et met les données de CCXT en cache'''
    cachePath = '{}.pkl'.format(market).replace('/', '-')
    if os.path.isfile(cachePath):
        cacheFile = open(cachePath, 'rb')
        dataFile = pickle.load(cacheFile)
        print('{} est chargé du cache'.format(market))
    else:
        dataFile = open(cachePath, 'wb')
        print('Charge de {} de CCXT'.format(market))
        exchange = ccxt.bittrex()
        dataFile = exchange.fetch_ohlcv(market, timeframe = '1m')
        dataFrame = pd.DataFrame(data=dataFile, columns=['timestamp', 'open', 'high', 'low', 'close', 'volume']).head(500)
        dataFrame.to_pickle(cachePath)        
        print('{} en cache dans {}'.format(market, cachePath))
    return dataFile
def loadData():
    '''charge les données historiques des cryptomonnaies choisies dans un dictionnaire'''
    altcoins = ['BTC/USD', 'ETH/BTC','XRP/BTC','BCH/BTC','LTC/BTC','XLM/BTC','ADA/BTC','TRX/BTC','XMR/BTC','NEO/BTC']
    for market in altcoins:
        altcoinsData[market] = getCCXTData(market)
        #print(altcoinsData[market])
        
def computeDollarsRate():
    '''effectue la conversion du taux crypto/BTC vers crypto/USD
    RETURN: dataframe'''
    altcoinsInDollars = {}
    for market in altcoinsData:
        if market != 'BTC/USD':
            altcoinsData[market]['rateBTCUSD'] = altcoinsData['BTC/USD']['close']
            altcoinsData[market]['rateUSD'] = altcoinsData[market]['close'] * altcoinsData[market]['rateBTCUSD']
            coin = market.split('/')[0]
        elif market == 'BTC/USD':
            altcoinsData[market]['rateUSD'] = altcoinsData['BTC/USD']['close']
            coin = 'BTC'
        altcoinsInDollars[coin] = altcoinsData[market]['rateUSD']
    return pd.DataFrame(altcoinsInDollars)
        
def plotData(dataFrame):
    '''compose un graphique sur base d'un dataframe'''
    for market in dataFrame:
        dataFrame[market].plot(grid=True,figsize=(8,5),label=market)
        
    plt.legend()
    plt.show()
    fig, ax = plt.subplots()
    plt.imshow(dataFrame, cmap='hot', interpolation='nearest')
    plt.colorbar()
    plt.show()
def computeCorrelation(dataFrame):
    return dataFrame.pct_change().corr(method='pearson')
    
if __name__ == '__main__':
    loadData()
    df = computeDollarsRate()
    print(df)
    df = computeCorrelation(df)
    print(df)
    plotData(df)
