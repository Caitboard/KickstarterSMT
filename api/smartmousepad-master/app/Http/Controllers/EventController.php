<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Event;

class EventController extends Controller
{
    public function show($event_id){
      $event = Event::where('event_id','=',$event_id)->first();

      return $event;
  }
}
