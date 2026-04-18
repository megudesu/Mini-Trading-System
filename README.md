# Mini Trading System in C++

## Overview
This project is a mini trading system implemented in C++.  
It simulates a basic exchange matching engine with a focus on order book mechanics and performance.


## Features
- Feed parser for processing market data
- Limit Order Book (LOB) with price-time priority
- Multi-level order matching across price levels
- Order cancellation using indexing
- Best bid and ask tracking (O(1) access)
- Order storage and updates using O(log N) structures


## Performance
Latency measured for core operations (add/match/cancel):

- Best case: ~0.5 µs  
- Average: ~4 µs  
- Worst case: ~9.7 µs  

Latency varies based on matching complexity and number of price levels traversed.


## How it Works
- Orders are parsed from an input data file
- Orders are added to the order book or matched against existing orders
- Matching follows price-time priority
- Orders can be partially filled across multiple price levels


## Project Structure
- `FeedHandler` → Handles parsing of input data
- `OrderBook` → Core matching engine
- `Data` → Input dataset


## Future Work
- Implement trading strategy
- Track profit and loss (PnL)
- Optimize latency and memory usage
