/**
 * Created by lance on 16-3-21.
 */
//constant
const ONE_DAY = 24*60*60;//one day.

var date_util = {
    getToday:function(){
        var today = new Date();
        today.setHours(0);
        today.setMinutes(0);
        today.setSeconds(0);
        today.setMilliseconds(0);
        return Math.floor(today.getTime()/1000);
    }
    ,getThisMonth:function(){
        var today = new Date();
        today.setDate(0);
        today.setHours(0);
        today.setMinutes(0);
        today.setSeconds(0);
        today.setMilliseconds(0);
        return Math.floor(today.getTime()/1000);
    }
    ,getNowTimestamp:function(){
        return Math.floor(new Date().getTime()/1000);
    }
};

/**
 * do job every time gap
 * @param job
 * @param options method's params
 * @param timegap unit:seconds
 */
var doJobBytimegap = function(job,options,timegap){
    job(options);
    setTimeout(function(){
        doJobBytimegap(job,options,timegap);
    },timegap * 1000);

};

/**
 * do job at specific time everyday
 * @param job
 * @param options
 */
var doJobEveryday = function(job,options){
    job(options);
    setTimeout(function(){
        doJobEveryday(job,options)
    },ONE_DAY * 1000);
};


/**
 * start the job everyday
 * @param targettime unit:seconds
 * @param job
 * @param options
 */
var startJobEveryDay = function(targettime,job,options){
    //the time to start
    var timegap = targettime - date_util.getNowTimestamp();
    setTimeout(function(){
        doJobEveryday(job,options);
    },timegap * 1000);
};

/**
 * start do the job every time gap
 * @param start_timestamp first time
 * @param timegap
 * @param job
 * @param options
 */
var startJobEveryTimegap = function(start_timestamp,timegap,job,options){
    var timetogo = start_timestamp - date_util.getNowTimestamp();
    setTimeout(function(){
        doJobBytimegap(job,options,timegap);
    },timetogo * 1000);
};

module.exports = {
    startJobEveryDay:startJobEveryDay
    ,startJobEveryTimegap:startJobEveryTimegap
    ,date_util:date_util
    ,ONE_DAY:ONE_DAY
};