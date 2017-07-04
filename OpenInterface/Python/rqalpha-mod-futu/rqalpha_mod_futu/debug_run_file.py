# -*- coding: utf-8 -*-

from rqalpha import run_file


config = {
  "base": {
    "start_date": "2016-01-01",
    "end_date": "2016-12-01",
    "accounts": {
      "stock": 100000
    },
    "benchmark": "HK.00700",
    "frequency": "1d",
    # 运行类型，`b` 为历史数据回测，`p` 为实时数据模拟交易, `r` 为实时数据实盘交易。
    "run_type":  "b",
  },
  "extra": {
    "log_level": "verbose",
  },
  "mod": {
    "sys_analyser": {
      "enabled": True,
      "plot": True
    },
    "sys_simulation":
    {
      'enabled': False,
    },
    "sys_stock_realtime":
    {
      'enabled': False,
    },
  }
}

# strategy_file_path = "./debug_strategy.py"  # OK
strategy_file_path = "./test_strategy.py"   # ERROR long_avg
# strategy_file_path = "./MACD.py"  # OK
# strategy_file_path = "./RSI.py"   # ERROR 多支股票
# strategy_file_path = "./Turtles.py"  # ERROE input lengths are different

run_file(strategy_file_path, config)
