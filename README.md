# Backtest

#### fastest trade backtesting alive

`backtest` is command-line tool and library for backtesting trading algorithms. Built in ANSI C, cross-platform, high performance. Well documented and lots of examples.

## Build

Build

```
make
```

and install

```
make install
```

## History file format
Single line is `yyyymmdd hhMMss;open;high;low;close`

## Usage

### Use as library and link statically on build-time (recommended)

1. Build a minimal strategy:

```
// strategy code here
```

1. Build using makefile. Example makefile
```
all:
	gcc *.c
```

### 

### Strategy template

```

```

### Options

* `--output-format` Default is `html`. Possible values are: `html`,`json`
* `--output-target` Default is `file`. Possible values are: `stdout`,`file`
* `--output-file` Default is `{date}-{time}-{strategy-file}-backtest.html`. Possible values are: `stdout`,`file`. Specifying this also sets `--output-target` to `file`.
* `--history-file` File containing history price data. Default is `history.csv`
* `--history-file-format` Force format of history data file. Default is `csv` but overridden . Possible values are `csv`,`bth`...
* `--history-file-period` Period to read values for from history file. Used when using 5 or 6 cols in CSV format. On 4 cols period is parsed from history filename. If none found `HOUR` is assumed. Possible values are `TICK`,`SECOND`,`MINUTE`,`HOUR`,`DAY`,`WEEK`,`MONTH`. TBD more periods
* `--history-file-csv-delimiter` 

* `--some-option` Meaning. Default is `default`. Possible values are ``,``...

### History format

#### CSV
	* 4 cols - OHLC - OPEN, HIGH, LOW, CLOSE
	* 5 cols - POHLC - PERIOD, OPEN, HIGH, LOW, CLOSE
	* 6 cols - IPOHLC - INSTRUMENT, PERIOD, OPEN, HIGH, LOW, CLOSE

## License

TBD
