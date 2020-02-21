//
// Created by 王镱霏 on 2/21/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <iostream>
//#include <fstream>
#include "column.h"
#include "row.h"
#include "dataframe.h"
#include "modified_dataframe.h"

using namespace std;


class Txt_reader :public Object{

public:
    Txt_reader()   {
//        _mdf = this->output();
}
public:ModifiedDataFrame* output(){
        //this is the order same as my dataset

        Schema sch("ISSIISSFFFFFSISSSSSSSSSSFFFFFSFFSBBBBBBBBBBBBBSSSS");
        ModifiedDataFrame* mdf = new ModifiedDataFrame(sch);

    FILE *fPointer;
    fPointer = fopen("/Users/wangyifei/gitcs4500/assignment5/part1/datafile.txt", "r");
    if (fPointer == NULL) {
        cerr << "File wouldn't open:" << strerror(errno) << "\n" << endl;
        return mdf;
    }
    //load column
    char singleLine[1024];
    char *token;
    const char s[2] = ",";

    int id;
    String *ID;
    String *source;
    int tmc;
    int severity;
    String *start_time;
    String *end_time;
    float start_lat;
    float start_lng;
    float end_lat;
    float end_lng;
    float distance;
    String *description;
    int num;
    String *street;
    String *side;
    String *city;
    String *county;
    String *state;
    String *zip;
    String *country;
    String *timezone;
    String *airport_code;
    String *weather_timestamp;
    float temperature;
    float wind_chill;
    float humidity;
    float pressure;
    float visibility;
    String *wind_direction;
    float wind_speed;
    float precipitation;
    String *weather_condition;
    bool amenity;
    bool bump;
    bool crossing;
    bool give_way;
    bool junction;
    bool no_exit;
    bool railway;
    bool roundabout;
    bool station;
    bool stop;
    bool traffic_calming;
    bool traffic_signal;
    bool turning_loop;
    String *sunrise_sunset;
    String *civil_twilight;
    String *nautical_twilight;
    String *astronomical_twilight;


    while (1) {
        fgets(singleLine, 1024, fPointer);
        puts(singleLine);
        token = strtok(singleLine, ",");

        id = (int) atoi(token);
        token = strtok(NULL, ",");
//        assert(token);
        if (token != 0){
        ID = new String(token);
        token = strtok(NULL, ",");
        source = new String(token);
        token = strtok(NULL, ",");
        tmc = (int) atoi(token);
        token = strtok(NULL, ",");
        severity = (int)atoi(token);
        token = strtok(NULL, ",");
        start_time = new String(token);
        token = strtok(NULL, ",");
        end_time = new String(token);
        token = strtok(NULL, ",");
        start_lat = (float) atoi(token);
        token = strtok(NULL, ",");
        start_lng = (float) atoi(token);
        token = strtok(NULL, ",");
        end_lat = (float) atoi(token);
        token = strtok(NULL, ",");
        end_lng = (float) atoi(token);
        token = strtok(NULL, ",");
        distance = (float) atoi(token);
        token = strtok(NULL, ",");
        description = new String(token);
        token = strtok(NULL, ",");
        num = (int)atoi(token);
        token = strtok(NULL, ",");
        street = new String(token);
        token = strtok(NULL, ",");
        side = new String(token);
        token = strtok(NULL, ",");
        city = new String(token);
        token = strtok(NULL, ",");
        county = new String(token);
        token = strtok(NULL, ",");
        state = new String(token);
        token = strtok(NULL, ",");
        zip = new String(token);
        token = strtok(NULL, ",");
        country = new String(token);
        token = strtok(NULL, ",");
        timezone = new String(token);
        token = strtok(NULL, ",");
        airport_code = new String(token);
        token = strtok(NULL, ",");
        weather_timestamp = new String(token);
        token = strtok(NULL, ",");
        temperature = (float)atoi(token);
        token = strtok(NULL, ",");
        wind_chill = (float)atoi(token);
        token = strtok(NULL, ",");
        humidity = (float)atoi(token);
        token = strtok(NULL, ",");
        pressure = (float)atoi(token);
        token = strtok(NULL, ",");
        visibility = (float)atoi(token);
        token = strtok(NULL, ",");
        wind_direction = new String(token);
        token = strtok(NULL, ",");
        wind_speed = (float)atoi(token);
        token = strtok(NULL, ",");
        precipitation = (float)atoi(token);
        token = strtok(NULL, ",");
        weather_condition = new String(token);
        token = strtok(NULL, ",");
        amenity = (bool)atoi(token);
        token = strtok(NULL, ",");
        bump = (bool)atoi(token);
        token = strtok(NULL, ",");
        crossing = (bool)atoi(token);
        token = strtok(NULL, ",");
        give_way = (bool)atoi(token);
        token = strtok(NULL, ",");
        junction = (bool)atoi(token);
        token = strtok(NULL, ",");
        no_exit = (bool)atoi(token);
        token = strtok(NULL, ",");
        railway = (bool)atoi(token);
        token = strtok(NULL, ",");
        roundabout = (bool)atoi(token);
        token = strtok(NULL, ",");
        station = (bool)atoi(token);
        token = strtok(NULL, ",");
        stop = (bool)atoi(token);
        token = strtok(NULL, ",");
        traffic_calming = (bool)atoi(token);
        token = strtok(NULL, ",");
        traffic_signal = (bool)atoi(token);
        token = strtok(NULL, ",");
        turning_loop = (bool)atoi(token);
        token = strtok(NULL, ",");
        sunrise_sunset = new String(token);
        token = strtok(NULL, ",");
        civil_twilight = new String(token);
        token = strtok(NULL, ",");
        nautical_twilight = new String(token);
        token = strtok(NULL, ",");
        astronomical_twilight = new String(token);
//        token = strtok(NULL, ",");

        Row r(sch);
        r.set(0,id);
        r.set(1,ID);
        r.set(2,source);
        r.set(3,tmc);
        r.set(4,severity);
        r.set(5,start_time);
        r.set(6,end_time);
        r.set(7,start_lat);
        r.set(8,start_lng);
        r.set(9, end_lat);
        r.set(10, end_lng);
        r.set(11,distance);
        r.set(12,description);
        r.set(13,num);
        r.set(14,street);
        r.set(15,side);
        r.set(16,city);
        r.set(17,county);
        r.set(18,state);
        r.set(19,zip);
        r.set(20,country);
        r.set(21,timezone);
        r.set(22,airport_code);
        r.set(23,weather_condition);
        r.set(24,temperature);
        r.set(25,wind_chill);
        r.set(26,humidity);
        r.set(27,pressure);
        r.set(28,visibility);
        r.set(29,wind_direction);
        r.set(30,wind_speed);
        r.set(31,precipitation);
        r.set(32,weather_condition);
        r.set(33,amenity);
        r.set(34,bump);
        r.set(35,crossing);
        r.set(36,give_way);
        r.set(37,junction);
        r.set(38,no_exit);
        r.set(39,railway);
        r.set(40,roundabout);
        r.set(41,station);
        r.set(42,stop);
        r.set(43,traffic_calming);
        r.set(44,traffic_signal);
        r.set(45,turning_loop);
        r.set(46,sunrise_sunset);
        r.set(47,civil_twilight);
        r.set(48,nautical_twilight);
        r.set(49,astronomical_twilight);
        mdf->add_row(r);

        } else{
            break;
        }
    }

    fclose(fPointer);

    delete ID;
    delete source;
    delete start_time;
    delete end_time;
    delete sunrise_sunset;
    delete civil_twilight;
    delete nautical_twilight;
    delete astronomical_twilight;
    delete weather_condition;
    delete wind_direction;
    delete description;
    delete street;
    delete side;
    delete city;
    delete county;
    delete state;
    delete zip;
    delete country;
    delete timezone;
    delete airport_code;
    delete weather_timestamp;


    return mdf;
    }
};