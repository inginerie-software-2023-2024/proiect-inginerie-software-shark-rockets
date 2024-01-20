# cron-job
node模块。功能是定时任务。cron job.Do something every day or at a specific time

# USAGE
> npm install cron-job

```js

var cronjob = require('cron-job');

var job = function(options){//only one parameters
    console.log('do job...'+JSON.stringify(options))
};

//do it after 5s,and do it every 3s
var first_time = cronjob.date_util.getNowTimestamp()+5;//timestamp,unit is seconds
var timegap = 3;//seconds
var options = {//method's parameters
    param1:'1'
    param2:'2'
};

cronjob.startJobEveryTimegap(first_time+5,timegap,job,options);

//do it at tomorrow's 0 o'clock,and do it every day.
var tomorrowtimestamp = cronjob.date_util.getToday()+cronjob.ONE_DAY;//it must bigger than the current timestamp,unit is seconds
var options = {//method's parameters
    param1:'1'
    param2:'2'
};

cronjob.startJobEveryDay(tomorrowtimestamp,job,options);

```

# API
* cron-job.startJobEveryTimegap(start_timestamp, timegap, job,options)
* cron-job.startJobEveryDay(targettime,job,options)
* cron-job.ONE_DAY:constant,24 * 60 * 60

> cron-job.date_util:

* getToday():get today's 0 o'clock timestamp
* getThisMonth(): get this month's first day's 0 o'clock timestamp
* getNowTimestamp(): current timestamp