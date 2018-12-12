package com.example.ds.fishealth;

import android.graphics.Color;
import android.os.Bundle;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.formatter.IFillFormatter;
import com.github.mikephil.charting.interfaces.dataprovider.LineDataProvider;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;

import java.util.ArrayList;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private LineChart chart;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        setupChart();
        setData(40,100f);

    }

    private void setupChart() {
        chart = findViewById(R.id.chart);
        chart.setViewPortOffsets(0,0,0,0);
        chart.setBackgroundColor(Color.rgb(104,241,175));

        // no description text
        chart.getDescription().setEnabled(false);

        // enable touch gestures
        chart.setTouchEnabled(true);

        // enable scaling and dragging
        chart.setDragEnabled(true);
        chart.setScaleEnabled(true);

        // if disabled, scaling can be done on x- and y-axis separately
        chart.setPinchZoom(false);

        chart.setDrawGridBackground(false);
        chart.setMaxHighlightDistance(300);

        XAxis x = chart.getXAxis();
        x.setEnabled(false);

        YAxis y = chart.getAxisLeft();
        y.setLabelCount(6, false);
        y.setTextColor(Color.WHITE);
        y.setPosition(YAxis.YAxisLabelPosition.INSIDE_CHART);
        y.setDrawGridLines(false);
        y.setAxisLineColor(Color.WHITE);

        chart.getAxisRight().setEnabled(false);

        chart.getLegend().setEnabled(false);

        chart.animateXY(2000, 2000);

        // don't forget to refresh the drawing
        chart.invalidate();
    }

    private void setData(int count, float range) {
        ArrayList<Entry> values = new ArrayList<>();
        for (int i=0; i<count; i++) {
            float val = (float) (Math.random() * (range + 1)) + 20;
            values.add(new Entry(i,val));
        }

        LineDataSet set;
        if (chart.getData() != null && chart.getData().getDataSetCount() > 0) {
            set = (LineDataSet) chart.getData().getDataSetByIndex(0);
            set.setValues(values);
            chart.getData().notifyDataChanged();
            chart.notifyDataSetChanged();
        } else {
            // create dataset and give it a type
            set = new LineDataSet(values, "DataSet 1");

            set.setMode(LineDataSet.Mode.CUBIC_BEZIER);
            set.setCubicIntensity(0.2f);
            set.setDrawFilled(true);
            set.setDrawCircles(true);
            set.setLineWidth(1.8f);
            set.setCircleRadius(4f);
            set.setHighLightColor(Color.rgb(244,177,117));
            set.setColor(Color.WHITE);
            set.setFillColor(Color.WHITE);
            set.setFillAlpha(100);
            set.setDrawHorizontalHighlightIndicator(false);
            set.setFillFormatter(new IFillFormatter() {
                @Override
                public float getFillLinePosition(ILineDataSet dataSet, LineDataProvider dataProvider) {
                    return chart.getAxisLeft().getAxisMinimum();
                }
            });

            // create a data object with the data sets
            LineData data = new LineData(set);
            data.setValueTextSize(9f);
            data.setDrawValues(false);

            // set data
            chart.setData(data);
        }
    }
}
