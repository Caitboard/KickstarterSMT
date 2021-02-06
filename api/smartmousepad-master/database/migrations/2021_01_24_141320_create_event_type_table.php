<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateEventTypeTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('event_type', function (Blueprint $table) {
            $table->integer('event_id')->unsigned();
            $table->foreign("event_id")->references("event_id")->on("event");
            $table->string("event_name");
            $table->string("event_description");
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::table('event_type', function($table){
          $table->dropForeign('event_type_event_id_foreign');
        });
        Schema::dropIfExists('event_type');
    }
}
