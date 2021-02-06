<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateAverageGroupTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('average_group', function (Blueprint $table) {
            $table->integer('group_id')->unsigned();
            $table->foreign('group_id')->references("group_id")->on("group");
            $table->datetime("datetime")->nullable();
            $table->double("group_average");
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
      Schema::table('average_group', function($table){
        $table->dropForeign('average_group_group_id_foreign');
      });
      Schema::dropIfExists('average_group');
    }
}
